# aramar Pedal-Board for KORG Kronos #

This is designed to be run on a TeensyLC as those boards can turn themselves into native USB-MIDI-devices.
This eliminates the need for DIN-5 plugs and for an external power-supply as the TeensyLC is USB-powered.

The hardware used for buttons, pedal, LEDs and display is an old Roland FC-200 that was disassembled and
refurnished with RGB-LEDs (PL9823-F5 aka WS2812 B).

The pin layout is as follows:

|PIN|Usage|Connection|
|---|---|---|
|01|MIDI RX|DIN5 MIDI Input|
|02|MIDI TX|DIN5 MIDI Output|
