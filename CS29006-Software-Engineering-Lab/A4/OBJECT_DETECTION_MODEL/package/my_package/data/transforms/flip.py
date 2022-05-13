
import numpy as np
from PIL import Image 


class FlipImage ( object ) :
    
    def __init__ ( self , type = 'horizontal' ) :
        self.flip_type = type
        
    def __call__ ( self , image ) :
        pixels = np.array( image )
        if ( self.flip_type == 'horizontal' ) :
            for i in range(len(pixels)) :
                pixels[i] = pixels[i][::-1]
            return pixels
        return np.flip(pixels, 0)


