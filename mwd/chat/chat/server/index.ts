import { WebSocket } from "ws";
import { runInterpreter } from "./interpreter_src/Parser";

enum MessageType {
    CONTROL,
    MESSAGE,
}

enum MessageSubType {
    WELCOME,
    ENTER,
    LEAVE,
    USERLIST,
    FORMULA,
    UNDEF,
}

class Message {
    constructor(
        public username: string,
        public type: MessageType,
        public subtype: MessageSubType,
        public text = "",
        public receiver: string = "",
        public response: string = ""
    ) {}
}

class ConnectionList {
    private items: Map<string, WebSocket> = new Map<string, WebSocket>();

    public findWebSocketByUser(username: string): WebSocket | undefined {
        return this.items.get(username);
    }

    public findUserByWebSocket(websocket: WebSocket): string | undefined {
        for (const [key, value] of this.items)
            if (value == websocket) return key;
        return undefined;
    }

    public add(username: string, webSocket: WebSocket) {
        this.items.set(username, webSocket);
    }

    public removeByName(username: string) {
        this.items.delete(username);
    }

    public listOfConnectedUsers(): Array<string> {
        return Array.from(this.items.keys());
    }
}

let connectionList = new ConnectionList();

function sendMessage(message: Message, receiver: string) {
    let ws = connectionList.findWebSocketByUser(receiver);
    if (ws !== undefined) ws.send(JSON.stringify(message));
}

function broadcastMessage(message: Message) {
    const calculateValue = (message: Message): string => {
        return runInterpreter(message.text);
    };

    message.response = calculateValue(message);
    console.log("calculated : " + message.response);
    console.log("text : " + message.text);
    console.log("connectionList.listOfConnectedUsers()", connectionList.listOfConnectedUsers());

    connectionList.listOfConnectedUsers().forEach((username) => {
      sendMessage(message, username);
    });
}

function processControl(webSocket: WebSocket, message: Message) {
    console.log("processControl");
    switch (message.subtype) {
        case MessageSubType.ENTER: {
            if (message.username == "") webSocket.close();
            else {
                if (
                    connectionList.findWebSocketByUser(message.username) ===
                    undefined
                ) {
                    connectionList.add(message.username, webSocket);
                    webSocket.send(
                        JSON.stringify(
                            new Message(
                                "",
                                MessageType.CONTROL,
                                MessageSubType.WELCOME
                            )
                        )
                    );
                    broadcastMessage(
                        new Message(
                            "",
                            MessageType.CONTROL,
                            MessageSubType.USERLIST,
                            JSON.stringify(
                                connectionList.listOfConnectedUsers()
                            )
                        )
                    );
                }
            }
            break;
        }

        case MessageSubType.LEAVE: {
            connectionList.removeByName(message.username);
            connectionList.findWebSocketByUser(message.username)?.close();
            broadcastMessage(
                new Message(
                    "",
                    MessageType.CONTROL,
                    MessageSubType.USERLIST,
                    JSON.stringify(connectionList.listOfConnectedUsers())
                )
            );
            break;
        }
    }
}

function processMessage(webSocket: WebSocket, message: Message) {
    console.log("processMessage");

    if (message.receiver != "") sendMessage(message, message.receiver);
    else broadcastMessage(message);
}

const webSocketServer = new WebSocket.Server({ port: 8888 });

webSocketServer.on("connection", (webSocket: WebSocket) => {
    console.log(
        `new connection - (${webSocketServer.clients.size} open connections)`
    );

    webSocket.on("message", (received: ArrayBuffer) => {
        console.log("received : " + received.toString());
        let message = JSON.parse(JSON.parse(received.toString()));
        console.log("received message type : " + typeof message);
        switch (message.type) {
            case MessageType.CONTROL:
                processControl(webSocket, message);
                break;
            case MessageType.MESSAGE:
                processMessage(webSocket, message);
                break;
        }
    });

    webSocket.on("close", () => {
        let username = connectionList.findUserByWebSocket(webSocket);
        console.log(`user ${username} closed socket.`);
        if (typeof username === "string") {
            console.log(`connection from user ${username} closed`);
            connectionList.removeByName(username);
        }
    });
});

console.log("Server running on port 8888");
