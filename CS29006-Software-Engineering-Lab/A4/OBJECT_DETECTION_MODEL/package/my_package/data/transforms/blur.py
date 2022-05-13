
import numpy as np
from PIL import Image , ImageFilter


class BlurImage ( object ) :
    
    def __init__ ( self , radius = 1 ) :
        self.radius = radius
        
    def __call__ ( self , image ) :
        pixels = np.array(image)
        radius = self.radius
        if radius == 0 :
            return pixels
        img = image
        if isinstance(image, np.ndarray) :
            img = Image.fromarray(np.uint8(image))
        arr = np.array( img.filter( ImageFilter.GaussianBlur(self.radius) ) )
        return arr
