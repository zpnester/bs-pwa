type t;



let subscribe: (t, ~userVisibleOnly: bool=?, 
    ~applicationServerKey: [`String(string) | `ArrayBuffer(Js.Typed_array.ArrayBuffer.t)]=?, unit) => 
    Js.Promise.t(SW_PushSubscription.t);


let urlB64ToUint8Array: string => Js.Typed_array.Uint8Array.t;

let getSubscription: t => Js.Promise.t(option(SW_PushSubscription.t));