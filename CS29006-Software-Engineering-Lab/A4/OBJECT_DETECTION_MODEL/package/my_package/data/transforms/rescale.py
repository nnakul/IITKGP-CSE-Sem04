
import numpy as np
from PIL import Image 


class RescaleImage(object) :
    
    def __init__(self, size) :
        self.output_size = size
        
    def __call__(self, image) :
        pixels = np.array(image)
        img = image
        if isinstance(image, np.ndarray) :
            img = Image.fromarray(np.uint8(image))
        if isinstance(self.output_size, tuple) :
            arr = np.array( img.resize(self.output_size) )
        else :
            if pixels.shape[0] < pixels.shape[1] :
                height = self.output_size
                width = int( pixels.shape[0] * height / pixels.shape[1] )
            else :
                width = self.output_size
                height = int( width * pixels.shape[1] / pixels.shape[0] )
            arr = np.array( img.resize((height, width)) )
        return arr
        
        
