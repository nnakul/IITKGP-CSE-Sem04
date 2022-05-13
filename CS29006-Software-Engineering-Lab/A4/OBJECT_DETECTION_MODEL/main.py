
#   PYTHON DATA SCIENCE ASSIGNMENT
#   ASSIGNMENT O3 -- QUESTION O2
#   NAKUL AGGARWAL  |   19CS10044
#   03.02.2021  to  17.02.2021


from my_package.data.transforms import *
from my_package.analysis import plot_boxes
from my_package.data.dataset import Dataset
from my_package.model import ObjectDetectionModel as ODM
from prettytable import PrettyTable
import matplotlib.patches as patches
import matplotlib.pyplot as plt
from PIL import Image
import numpy as np
import json


def experiment_analysis_task_part_O1 ( annotation_file , detector , transforms , outputs ) :
    print('\n')
    dataset = Dataset(annotation_file, transforms)
    predicted_bounding_boxes = dict()
    for i in range(len(dataset)) :
        print('\n')
        print(' DETECTING OBJECTS IN THE', str(i) + 'th IMAGE OF THE DATASET ...')
        image_mod = dataset[i]['image']
        pred_boxes, pred_class, pred_score = detector(image_mod)
        if i == 0 or i == 2 : plot_boxes(image_mod, pred_boxes, pred_class, 'ANALYSIS_TASK_O1_IMG'+str(i)+'.jpg', outputs, 'adjust')
        elif i == 1 : plot_boxes(image_mod, pred_boxes, pred_class, 'ANALYSIS_TASK_O1_IMG'+str(i)+'.jpg', outputs, 'bottom')
        else :  plot_boxes(image_mod, pred_boxes, pred_class, 'ANALYSIS_TASK_O1_IMG'+str(i)+'.jpg', outputs)
        table = PrettyTable(['BOUNDARY BOX CONFIGURATION', 'OBJECT NAME', 'PREDICTION SCORE'])
        predicted_bounding_boxes['imgs/'+str(i)+'.jpg'] = list()
        for j in range(0,min(len(pred_boxes), 5)) :
            box = dict()
            box['bbox'] = [(float(pred_boxes[j][0][0]), float(pred_boxes[j][0][1])), (float(pred_boxes[j][1][0]), float(pred_boxes[j][1][1]))]
            box['category'] = pred_class[j]
            box['score'] = float(pred_score[j])
            predicted_bounding_boxes['imgs/'+str(i)+'.jpg'].append(box)
            table.add_row([pred_boxes[j], pred_class[j], pred_score[j]])
        print(table)
    
    json_object = json.dumps(predicted_bounding_boxes, indent = 4)
    with open(outputs+"/ANALYSIS_TASK_PART_O1.json", "w") as outfile : 
        outfile.write(json_object)


def experiment_analysis_task_part_O2 ( annotation_file , detector , roll_no , outputs ) :
    id = eval(roll_no[-1])
    print('\n\n\n    [ ACCORDING TO THE GIVEN ROLL NO., ANALYSIS WILL BE PERFORMED ON IMG ' + str(id) + ' IN THE DATASET ]\n\n')
    
    print(' DETECTING OBJECTS IN THE ORIGINAL IMAGE ...')
    dataset = Dataset(annotation_file)
    image = dataset[id]['image']
    pred_boxes, pred_class, pred_score = detector(image)
    plot_boxes(image, pred_boxes, pred_class, 'ANALYSIS_TASK_O2_A.jpg', outputs)
    table = PrettyTable(['BOUNDARY BOX CONFIGURATION', 'OBJECT NAME', 'PREDICTION SCORE'])
    for i in range(0,min(len(pred_boxes), 5)) :
        table.add_row([pred_boxes[i], pred_class[i], pred_score[i]])
    print(table)

    print('\n\n DETECTING OBJECTS IN THE HORIZONTALLY FLIPPED IMAGE ...')
    dataset = Dataset(annotation_file, [FlipImage()])
    image = dataset[id]['image']
    pred_boxes, pred_class, pred_score = detector(image)
    plot_boxes(image, pred_boxes, pred_class, 'ANALYSIS_TASK_O2_B.jpg', outputs)
    table = PrettyTable(['BOUNDARY BOX CONFIGURATION', 'OBJECT NAME', 'PREDICTION SCORE'])
    for i in range(0,min(len(pred_boxes), 5)) :
        table.add_row([pred_boxes[i], pred_class[i], pred_score[i]])
    print(table)

    print('\n\n DETECTING OBJECTS IN THE BLURRED IMAGE ...')
    dataset = Dataset(annotation_file, [BlurImage(3)])
    image = dataset[id]['image']
    pred_boxes, pred_class, pred_score = detector(image)
    plot_boxes(image, pred_boxes, pred_class, 'ANALYSIS_TASK_O2_C.jpg', outputs)
    table = PrettyTable(['BOUNDARY BOX CONFIGURATION', 'OBJECT NAME', 'PREDICTION SCORE'])
    for i in range(0,min(len(pred_boxes), 5)) :
        table.add_row([pred_boxes[i], pred_class[i], pred_score[i]])
    print(table)

    dataset = Dataset(annotation_file)
    image = dataset[id]['image']
    h , w = image.shape[1] * 2 , image.shape[2] * 2

    print('\n\n DETECTING OBJECTS IN THE TWICE RESCALED IMAGE ...')
    dataset = Dataset(annotation_file, [RescaleImage((w, h))])
    image = dataset[id]['image']
    pred_boxes, pred_class, pred_score = detector(image)
    plot_boxes(image, pred_boxes, pred_class, 'ANALYSIS_TASK_O2_D.jpg', outputs)
    table = PrettyTable(['BOUNDARY BOX CONFIGURATION', 'OBJECT NAME', 'PREDICTION SCORE'])
    for i in range(0,min(len(pred_boxes), 5)) :
        table.add_row([pred_boxes[i], pred_class[i], pred_score[i]])
    print(table)

    print('\n\n DETECTING OBJECTS IN THE HALF RESCALED IMAGE ...')
    h , w = round(h / 4) , round(w / 4)
    dataset = Dataset(annotation_file, [RescaleImage((w, h))])
    image = dataset[id]['image']
    pred_boxes, pred_class, pred_score = detector(image)
    plot_boxes(image, pred_boxes, pred_class, 'ANALYSIS_TASK_O2_E.jpg', outputs)
    table = PrettyTable(['BOUNDARY BOX CONFIGURATION', 'OBJECT NAME', 'PREDICTION SCORE'])
    for i in range(0,min(len(pred_boxes), 5)) :
        table.add_row([pred_boxes[i], pred_class[i], pred_score[i]])
    print(table)

    print('\n\n DETECTING OBJECTS IN THE 90° RIGHT ROTATED IMAGE ...')
    dataset = Dataset(annotation_file, [RotateImage(270)])
    image = dataset[id]['image']
    pred_boxes, pred_class, pred_score = detector(image)
    plot_boxes(image, pred_boxes, pred_class, 'ANALYSIS_TASK_O2_F.jpg', outputs, 'bottom')
    table = PrettyTable(['BOUNDARY BOX CONFIGURATION', 'OBJECT NAME', 'PREDICTION SCORE'])
    for i in range(0,min(len(pred_boxes), 5)) :
        table.add_row([pred_boxes[i], pred_class[i], pred_score[i]])
    print(table)

    print('\n\n DETECTING OBJECTS IN THE 45° LEFT ROTATED IMAGE ...')
    dataset = Dataset(annotation_file, [RotateImage(45)])
    image = dataset[id]['image']
    pred_boxes, pred_class, pred_score = detector(image)
    plot_boxes(image, pred_boxes, pred_class, 'ANALYSIS_TASK_O2_G.jpg', outputs, 'adjust')
    table = PrettyTable(['BOUNDARY BOX CONFIGURATION', 'OBJECT NAME', 'PREDICTION SCORE'])
    for i in range(0,min(len(pred_boxes), 5)) :
        table.add_row([pred_boxes[i], pred_class[i], pred_score[i]])
    print(table)
    print('\n\n')


transforms = list()
experiment_analysis_task_part_O1 ("annotations.jsonl", ODM(), transforms, "outputs")
experiment_analysis_task_part_O2 ("annotations.jsonl", ODM(), "19CS10044", "outputs")