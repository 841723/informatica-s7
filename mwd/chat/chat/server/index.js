"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var ws_1 = require("ws");
var Parser_1 = require("./interpreter_src/Parser");
var MessageType;
(function (MessageType) {
    MessageType[MessageType["CONTROL"] = 0] = "CONTROL";
    MessageType[MessageType["MESSAGE"] = 1] = "MESSAGE";
})(MessageType || (MessageType = {}));
var MessageSubType;
(function (MessageSubType) {
    MessageSubType[MessageSubType["WELCOME"] = 0] = "WELCOME";
    MessageSubType[MessageSubType["ENTER"] = 1] = "ENTER";
    MessageSubType[MessageSubType["LEAVE"] = 2] = "LEAVE";
    MessageSubType[MessageSubType["USERLIST"] = 3] = "USERLIST";
    MessageSubType[MessageSubType["FORMULA"] = 4] = "FORMULA";
    MessageSubType[MessageSubType["UNDEF"] = 5] = "UNDEF";
})(MessageSubType || (MessageSubType = {}));
var Message = /** @class */ (function () {
    function Message(username, type, subtype, text, receiver, response) {
        if (text === void 0) { text = ""; }
        if (receiver === void 0) { receiver = ""; }
        if (response === void 0) { response = ""; }
        this.username = username;
        this.type = type;
        this.subtype = subtype;
        this.text = text;
        this.receiver = receiver;
        this.response = response;
    }
    return Message;
}());
var ConnectionList = /** @class */ (function () {
    function ConnectionList() {
        this.items = new Map();
    }
    ConnectionList.prototype.findWebSocketByUser = function (username) {
        return this.items.get(username);
    };
    ConnectionList.prototype.findUserByWebSocket = function (websocket) {
        for (var _i = 0, _a = this.items; _i < _a.length; _i++) {
            var _b = _a[_i], key = _b[0], value = _b[1];
            if (value == websocket)
                return key;
        }
        return undefined;
    };
    ConnectionList.prototype.add = function (username, webSocket) {
        this.items.set(username, webSocket);
    };
    ConnectionList.prototype.removeByName = function (username) {
        this.items.delete(username);
    };
    ConnectionList.prototype.listOfConnectedUsers = function () {
        return Array.from(this.items.keys());
    };
    return ConnectionList;
}());
var connectionList = new ConnectionList();
function sendMessage(message, receiver) {
    var ws = connectionList.findWebSocketByUser(receiver);
    if (ws !== undefined)
        ws.send(JSON.stringify(message));
}
function broadcastMessage(message) {
    var calculateValue = function (message) {
        return (0, Parser_1.runInterpreter)(message.text);
    };
    message.response = calculateValue(message);
    console.log("calculated : " + message.response);
    console.log("text : " + message.text);
    console.log("connectionList.listOfConnectedUsers()", connectionList.listOfConnectedUsers());
    connectionList.listOfConnectedUsers().forEach(function (username) {
        sendMessage(message, username);
    });
}
function processControl(webSocket, message) {
    var _a;
    console.log("processControl");
    switch (message.subtype) {
        case MessageSubType.ENTER: {
            if (message.username == "")
                webSocket.close();
            else {
                if (connectionList.findWebSocketByUser(message.username) ===
                    undefined) {
                    connectionList.add(message.username, webSocket);
                    webSocket.send(JSON.stringify(new Message("", MessageType.CONTROL, MessageSubType.WELCOME)));
                    broadcastMessage(new Message("", MessageType.CONTROL, MessageSubType.USERLIST, JSON.stringify(connectionList.listOfConnectedUsers())));
                }
            }
            break;
        }
        case MessageSubType.LEAVE: {
            connectionList.removeByName(message.username);
            (_a = connectionList.findWebSocketByUser(message.username)) === null || _a === void 0 ? void 0 : _a.close();
            broadcastMessage(new Message("", MessageType.CONTROL, MessageSubType.USERLIST, JSON.stringify(connectionList.listOfConnectedUsers())));
            break;
        }
    }
}
function processMessage(webSocket, message) {
    console.log("processMessage");
    if (message.receiver != "")
        sendMessage(message, message.receiver);
    else
        broadcastMessage(message);
}
var webSocketServer = new ws_1.WebSocket.Server({ port: 8888 });
webSocketServer.on("connection", function (webSocket) {
    console.log("new connection - (".concat(webSocketServer.clients.size, " open connections)"));
    webSocket.on("message", function (received) {
        console.log("received : " + received.toString());
        var message = JSON.parse(JSON.parse(received.toString()));
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
    webSocket.on("close", function () {
        var username = connectionList.findUserByWebSocket(webSocket);
        console.log("user ".concat(username, " closed socket."));
        if (typeof username === "string") {
            console.log("connection from user ".concat(username, " closed"));
            connectionList.removeByName(username);
        }
    });
});
console.log("Server running on port 8888");
