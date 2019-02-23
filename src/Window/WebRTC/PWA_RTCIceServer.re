type t;

[@bs.obj] external make: (
	 ~credential: string=?,
	~credentialType: string=?,
	~urls: array(string),
	unit) => _ = "";
