import {Component} from '@angular/core';
import {FormsModule} from '@angular/forms';
import {StateService} from '../../services/state.service';
import {Message, MessageSubType, MessageType} from '../../classes/message';

@Component( {
   selector: 'app-connect-form',
   imports: [
      FormsModule
   ],
   templateUrl: './connect-form.component.html',
   standalone: true,
   styleUrl: './connect-form.component.css'
} )
export class ConnectFormComponent
{
   public server: string = "localhost:8888";
   public username: string = "User" + Math.ceil(Math.random() * 10000).toString();

   constructor( public stateService: StateService )
   {
   }

   public connect()
   {
      this.stateService.connect( this.server );
      this.stateService.username = this.username;
      this.stateService.sendMessage( new Message( this.username, MessageType.CONTROL, MessageSubType.ENTER ) );
   }
}
