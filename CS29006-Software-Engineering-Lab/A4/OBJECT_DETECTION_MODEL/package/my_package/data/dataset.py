
import json
from PIL import Image
import numpy as np


class Dataset(object):
    
    def __init__ ( self , annotation_file , transforms = [] ) :
        self.annotation_file = annotation_file
        self.transforms = transforms
        
    def __len__ ( self ) :
        with open( self.annotation_file , 'r' ) as json_file :
            json_list = list(json_file)
        return len(json_list)
        
    def __getitem__ ( self , idx ) :
        with open( self.annotation_file , 'r' ) as json_file :
            json_list = list(json_file)
        data = None
        count = -1
        for json_str in json_list :
            data = json.loads(json_str)
            count += 1
            if count == idx :   break
        RESULT = dict()
        RESULT['image'] = np.array( Image.open(data['img_fn']) )
        RESULT['gt_bboxes'] = list()
        for box in data['bboxes'] :
            RESULT['gt_bboxes'].append( [ box['category'] ] + box['bbox'] )
        for t in self.transforms :
            RESULT['image'] = t( RESULT['image'] )
        RESULT['image'] = RESULT['image'].swapaxes(1, 2).swapaxes(0, 1) / 255
        return RESULT


