## Robot Hand → Herny
## Sensorised Glove → Will

The operator is the one commanding the motion. Their finger position is the input. This means that when Henry makes contact with something, the break system will stop the user from being able to move their finger. This will make it so that Henry's finger position matches Will's anyways since the user is the one that controls the fingers.

You actually don't need encoders or anything on Will since the clamp will resist you at that position. So technically the servos from Will and the servos in Henry don't need to be connected. The real calibration will be between the flex resistors on Will and the servos on Henry.

So the two directions are not symmetric, and that's the whole resolution:

- Forward (command): will bend → mapped (calibrated, because kinematics differ) → henry servo target. Angle translation lives here.
- Return (feedback): henry fingertip force → one bit (contact / no contact) → will brake locks at current position. No angle translation at all.

Start instead of doing a full build, do it so that you can test that the haptics work with using only one finger on the sensorised glove.

Henry design: https://www.thingiverse.com/thing:2269115

Henry's design might have to be tweaked though to include wrist rotation and IMU implementation. On top of this, it will need space to include the force sensors. I'm sure that with long nough wires it will be okay. The ESP can also be attached on the outside of the forearm. Use maybe planetary gear for the wrist rotation? 

TODO: Research gears