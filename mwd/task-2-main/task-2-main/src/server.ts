import  WebSocket, {WebSocketServer} from "ws"
import { runInterpreter } from "./interpreter_src/Parser";

let port: number = 8000;
const webSocketServer = new WebSocketServer({port:port})

console.log("Started Server on port: " + port)

webSocketServer.on('connection', (webSocket: WebSocket) => {
    console.log(`Client connected`)

    webSocket.on("message",(message: string) => {
        console.log(`Message from client: ${message}`)
        console.log("Computing output")
        webSocket.send(runInterpreter(message.toString()));
    })

    webSocket.on("close", () => {
        console.log("Closed")
    })
})