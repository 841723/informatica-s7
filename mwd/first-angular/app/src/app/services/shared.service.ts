import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class SharedService {
  data: string[] = [];

  getData(): string[] {
    return this.data;
  }

  addData(data: string): void {
    this.data.push(data);
  }
  
  constructor() { }
}
