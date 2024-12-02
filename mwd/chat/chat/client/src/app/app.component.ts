import {Component} from '@angular/core';
import {StateService} from './services/state.service';
import {ConnectFormComponent} from './components/connect-form/connect-form.component';
import {MessageFormComponent} from './components/message-form/message-form.component';
import {MessageListComponent} from './components/message-list/message-list.component';

@Component( {
  selector: 'app-root',
   imports: [ConnectFormComponent, MessageFormComponent, MessageListComponent],
  templateUrl: './app.component.html',
  standalone: true,
  styleUrl: './app.component.css'
} )
export class AppComponent
{
  title = 'Chat-client';

  constructor( public stateService: StateService )
  {
  }
}
