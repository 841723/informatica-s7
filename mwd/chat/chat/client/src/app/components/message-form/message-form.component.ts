import {Component} from '@angular/core';
import {StateService} from '../../services/state.service';
import {Message, MessageSubType, MessageType} from '../../classes/message';
import {FormsModule} from '@angular/forms';

@Component( {
   selector: 'app-message-form',
   imports: [
      FormsModule
   ],
   standalone: true,
   templateUrl: './message-form.component.html',
   styleUrl: './message-form.component.css'
} )
export class MessageFormComponent
{
   public message: string = "";

   constructor( public stateService: StateService )
   {
   }

   public send()
   {
      let mess = new Message( this.stateService.username, MessageType.MESSAGE, MessageSubType.UNDEF, this.message );
      this.stateService.sendMessage( mess );
   }
}
