type t;

/*[@bs.new] external make: unit => t = "MediaSource";*/

let make: unit => t = [%raw
  {|
function(unit) {
	return new MediaSource();
}
|}
];

/* TODO */
