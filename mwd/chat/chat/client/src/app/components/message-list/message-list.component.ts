import {Component, Input} from '@angular/core';
import {Message} from '../../classes/message';
import {StateService} from '../../services/state.service';

@Component( {
   selector: 'app-message-list',
   imports: [],
   standalone: true,
   templateUrl: './message-list.component.html',
   styleUrl: './message-list.component.css'
} )
export class MessageListComponent
{
   @Input() messages!: Array<Message>;
   protected _title:string = "Message List";

   constructor(public stateService:StateService)
   {
   }
}
