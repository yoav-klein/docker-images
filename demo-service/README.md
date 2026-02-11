# Demo Service

## Context
In order to develop the new deployment process, I needed an image to simulate a service.
Basically all I need from it is to print environment variables, to test the passing of the correct environemnt variables
to the Helm charts.
I also need to see the version, so the Dockerfile takes a VERSION argument so that when I create the image I create it with the correct 
version baked in the image

