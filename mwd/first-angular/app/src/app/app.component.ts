import { Component } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { MessageListComponent } from './components/message-list/message-list.component';
import { MessageInputComponent } from './components/message-input/message-input.component';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [RouterOutlet, MessageListComponent, MessageInputComponent],
  templateUrl: './app.component.html',
  styleUrl: './app.component.css'
})
export class AppComponent {
  title = 'app';
}
