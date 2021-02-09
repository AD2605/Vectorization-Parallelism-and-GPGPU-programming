This part of the Repo contains most common activation functions. 
Currently has `ReLU` and `Leaky ReLU` for cpu, sycl and cuda devices. 
I have made sure that the code does not diverge.


#### Known Issues. 
Currently, 'Leaky ReLU' does not support custom slopes and defaults to 0.5 for negative inputs and 1 for positive ones. 
This is yet to be done.
