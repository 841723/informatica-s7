export enum MessageType
{
  CONTROL,
  MESSAGE
}

export enum MessageSubType
{
  WELCOME,
  ENTER,
  LEAVE,
  USERLIST,
  UNDEF
}

export class Message {
  constructor( public username: string,
               public type: MessageType,
               public subtype: MessageSubType,
               public text = "",
               public receiver: string = "",
               public response: string = "" )
  {};
}
