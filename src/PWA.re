module ServiceWorkerGlobalScope = PWA_ServiceWorkerGlobalScope;
module ServiceWorkerRegistration = PWA_ServiceWorkerRegistration;
module ServiceWorker = PWA_ServiceWorker;
module Client = PWA_Client;
module ClientType = PWA_ClientType;
module Clients = PWA_Clients;
module Notification = PWA_Notification;
module NotificationEvent = PWA_NotificationEvent;
module Notification_Action = PWA_Notification_Action;
module WindowClient = PWA_WindowClient;
module PushMessageData = PWA_PushMessageData;
module MessagePort = PWA_MessagePort;
module Event = PWA_Event;
module ErrorEvent = PWA_ErrorEvent;
module MessageEvent = PWA_MessageEvent;
module PushEvent = PWA_PushEvent;
module InstallEvent = PWA_InstallEvent;
module SyncEvent = PWA_SyncEvent;
module PushSubscriptionChangeEvent = PWA_PushSubscriptionChangeEvent;
module ActivateEvent = PWA_ActivateEvent;
module PushManager = PWA_PushManager;
module PushSubscription = PWA_PushSubscription;

module Window = PWA_Window;
module Document = PWA_Document;
module ServiceWorkerContainer = PWA_ServiceWorkerContainer;
module Navigator = PWA_Navigator;
module MediaDevices = PWA_MediaDevices;
module MediaStream = PWA_MediaStream;
module MediaStreamTrack = PWA_MediaStreamTrack;
module HTMLVideoElement = PWA_HTMLVideoElement;
module HTMLAudioElement = PWA_HTMLAudioElement;
module HTMLCanvasElement = PWA_HTMLCanvasElement;
module CanvasRenderingContext2D = PWA_CanvasRenderingContext2D;
module HTMLInputElement = PWA_HTMLInputElement;
module HTMLButtonElement = PWA_HTMLButtonElement;
module HTMLSelectElement = PWA_HTMLSelectElement; 
module HTMLOptionElement = PWA_HTMLOptionElement;
module HTMLTextAreaElement = PWA_HTMLTextAreaElement;
module URL = PWA_URL;

module RTCPeerConnection = PWA_RTCPeerConnection;
module RTCDataChannel = PWA_RTCDataChannel;
module RTCCertificate = PWA_RTCCertificate;
module RTCDtlsTransport = PWA_RTCDtlsTransport;
module RTCIceCandidate = PWA_RTCIceCandidate;
module RTCIceServer = PWA_RTCIceServer;
module RTCRtpReceiver = PWA_RTCRtpReceiver;
module RTCRtpSender = PWA_RTCRtpSender;
module RTCRtpTransceiver = PWA_RTCRtpTransceiver;
module RTCSessionDescription = PWA_RTCSessionDescription;
module RTCPeerConnectionIceEvent = PWA_RTCPeerConnectionIceEvent;


 /*[@bs.send]
  external addEventListener: ('t, PWA_EventType.t('t, 'a), 'a => unit) => unit =
    "addEventListener";

  [@bs.send]
  external removeEventListener: ('t, PWA_EventType.t('t, 'a), 'a => unit) => unit =
    "removeEventListener";*/


 /*    [@bs.send]
  external addEventListener2: ('t, PWA_EventType.t2('t, 'a, 'b), ('a, 'b) => unit) => unit =
    "addEventListener";

  [@bs.send]
  external removeEventListener2: ('a, PWA_EventType.t2('t, 'a, 'b), ('a, 'b) => unit) => unit =
    "removeEventListener";*/
