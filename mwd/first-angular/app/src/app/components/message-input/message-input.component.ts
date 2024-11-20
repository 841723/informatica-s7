import { Component, NgModule } from '@angular/core';
import { SharedService } from '../../services/shared.service';
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-message-input',
  standalone: true,
  imports: [FormsModule],
  templateUrl: './message-input.component.html',
  styleUrl: './message-input.component.css',
})
export class MessageInputComponent {
  data: string[];
  newItem: string;
  constructor(private sharedService: SharedService) {
    this.data = sharedService.getData();
    this.newItem = '';
  }
  addItem() {
    this.sharedService.addData(this.newItem);
    this.newItem = '';
  }
}
