// {SinOsc.ar(220!8)}.play;  //for channel testing

OSCdef.new(
	\rate,
	{
		arg msg, time, addr, port;
		[msg, time, addr, port].postln;
		p.set(\rate, msg[1]);
		p.set(\trig, 1);
	},
	'/togglePlay'
);
OSCdef.new(
	\mute,
	{
		arg msg, time, addr, port;
		[msg, time, addr, port].postln;
		p.set(\mute, msg[1]);
	},
	'/toggleMute'
);
OSCdef.new(
	\trig,
	{
		arg msg, time, addr, port;
		[msg, time, addr, port].postln;
		p.set(\trig, msg[1]);
	},
	'/resetTrigger'
);
OSCdef.new(
	\pos,
	{
		arg msg, time, addr, port;
		[msg, time, addr, port].postln;
		p.set(\pos, 0);
		p.set(\rate, 0);
		p.set(\trig, 0);
	},
	'/reset'
);
OSCdef.new(
	\skip,
	{
		arg msg, time, addr, port;
		[msg, time, addr, port].postln;
		p.set(\pos, msg[1]);
		p.set(\rate, 0);
		p.set(\trig, 0);
	},
	'/skipTo'
);

o = OSCFunc({ arg msg, time, addr, recvPort; [msg, time, addr, recvPort].postln; }, '/goodbye', n);
// OSCFunc.trace(true); // Turn posting on
// OSCFunc.trace(false); // Turn posting off


b = Buffer.alloc(s, s.sampleRate*60*60, 8);
b = Buffer.read(s, "/Users/matze/Desktop/oF/of_v0.9.2_osx_release/apps/myApps/MultichannelAVPlayer/bin/data/BERLIOZ_COMPLETE_8N.wav");

/*c = Buffer.alloc(s, s.sampleRate*2)
c = Buffer.read(s, "/Users/matze/Downloads/Radiohead - A Moon Shaped Pool (16-bit WAV)/02 - Daydreaming.wav")*/

(
SynthDef(\player, { arg trig=0, rate=0, pos=0, mute=1.0;
    Out.ar(0,
		PlayBuf.ar(8, b.bufnum, rate, trig, pos, doneAction:0)*mute)
}).add;
)

p = Synth.new(\player, [\rate, 0.0]);


p.free
p.set(\trig, 0);
p.set(\trig, 1);
p.set(\pos, 0);
p.set(\rate, 0);
