import WebSocket from 'ws';
import * as readline from 'readline';

function promptFormula(ws: WebSocket) {
  rl.question('Enter your Formula: ', (answer) => {
    console.log(`Sending formula to server: ${answer}`);
    ws.send(answer);
  });
}


const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

const ws = new WebSocket('ws://localhost:8000');

ws.on('open', () => {
  console.log('Connected to server');
  promptFormula(ws);
 });

ws.on('message', (message: string) => {
  console.log(`Formula output: ${message}`);
  promptFormula(ws);
});


ws.on('close', () => {
  console.log('Disconnected from server');
});