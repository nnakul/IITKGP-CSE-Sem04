
import numpy as np
from PIL import Image


class RotateImage(object):
    
    def __init__(self, degrees):
        self.degrees = degrees

    def __call__(self, image):
        img = image
        if isinstance(image, np.ndarray) :
            img = Image.fromarray(np.uint8(image))
        arr = np.array( img.rotate(self.degrees, expand=1, fillcolor=(255,)*3) )
        return arr
        
        
        
        

