## Robot Hand → Herny
## Sensorised Glove → Will

The operator is the one commanding the motion. Their finger position is the input. This means that when Henry makes contact with something, the break system will stop the user from being able to move their finger. This will make it so that Henry's finger position matches Will's anyways since the user is the one that controls the fingers.

You actually don't need encoders or anything on Will since the clamp will resist you at that position. So technically the servos from Will and the servos in Henry don't need to be connected. The real calibration will be between the flex resistors on Will and the servos on Henry.

So the two directions are not symmetric, and that's the whole resolution:

- Forward (command): will bend → mapped (calibrated, because kinematics differ) → henry servo target. Angle translation lives here.
- Return (feedback): henry fingertip force → one bit (contact / no contact) → will brake locks at current position. No angle translation at all.