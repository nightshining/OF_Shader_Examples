# OF_Shader_Examples
A few different approaches to including shaders in openframeworks.


###Shader ISF Class Example:

This example utilizes the [ofxISF](https://github.com/satoruhiga/ofxISF) addon. It is a compilation of about a dozen ISF shaders that can be chained together to make interesting visual effects. In the example I use the shaders over a video but you can also throw it over images or FBO's. I did not personally write any of the shaders included in the example. They were found at the [ISF Shader Playground](http://www.interactiveshaderformat.com/). Currently, my example uses one big class to utilize all of the shaders. If any developers are willing to do a pull to clean it up, or just offer some advice on how to minimize the code that would be greatly appreciated. Thank you in advance. 

###Shader Playground Example:

This is an example of simply porting of a folder full of shaders from [Shader Toy](https://www.shadertoy.com/). Once again, I did not write the shaders myself. They were made by some really generous people who had uploaded their work to the previous website. Unfortunately, I have yet to understand how to chain these shaders together, so unlike the above example you cannot to effect chains. However, this does serve as a nice example on porting over shaders from the shadertoy website and playing with numbers to help learn GLSL language.
