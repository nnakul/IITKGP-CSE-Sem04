
import numpy as np
from PIL import Image 
from random import randint


class CropImage ( object ) :

    def __init__ ( self , shape , type = 'center' ) :
        self.shape = shape
        self.crop_type = type
        
    def __call__ ( self , image ) :
        pixels = np.array(image)
        center = ( pixels.shape[0] / 2 , pixels.shape[1] / 2 )
        top = int( center[0] - self.shape[0] / 2 )
        left = int( center[1] - self.shape[1] / 2 )
        if self.crop_type == 'random' :
            col_max = pixels.shape[1] - 1 - self.shape[1]
            row_max = pixels.shape[0] - 1 - self.shape[0]
            top = randint( 0 , row_max )
            left = randint( 0 , col_max )
        bottom = top + self.shape[0] - 1
        right = left + self.shape[1] - 1
        return pixels[ top:bottom , left:right , 0: ]
        



 