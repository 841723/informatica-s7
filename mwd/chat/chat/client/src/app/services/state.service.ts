import {Injectable} from '@angular/core';
import {Message, MessageType} from '../classes/message';
import {webSocket, WebSocketSubject} from 'rxjs/webSocket';

@Injectable( {
   providedIn: 'root'
} )
export class StateService
{

   private _Messages: Array<Message> = new Array<Message>();
   private connectedSocket: WebSocketSubject<string> | null = null;
   public username: string = "";

   constructor() { }

   get Messages(): Array<Message>
   {
      return this._Messages;
   }

   get isConnected(): boolean
   {
      return this.connectedSocket != null;
   }

   public sendMessage( message: Message )
   {
      if ( this.connectedSocket != null )
      {
         this.connectedSocket.next( JSON.stringify( message ) );
         console.log( "sendMessage : " + JSON.stringify( message ) );
         if ( message.type == MessageType.MESSAGE ) {}
            // this.Messages.push( message );
      }
   }

   private processMessage( message: any )
   {
      console.log( "processMessage" );
      this.Messages.push( message );
   }

   private processControl( message: any )
   {
      console.log( "processControl" );
   }

   private processData( data: any )
   {
      console.log( "received:",data );
      switch ( data['type'] )
      {
         case MessageType.CONTROL:
            this.processControl( data );
            break;
         case MessageType.MESSAGE:
            this.processMessage( data );
            break;
      }
   }

   public connect( url: string ): boolean
   {
      this.connectedSocket = webSocket( "ws://" + url );
      this.connectedSocket.asObservable().subscribe( data => this.processData( data ) );
      console.log( "connected" );
      return this.isConnected;
   }
}
