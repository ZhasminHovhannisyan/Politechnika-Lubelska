import cv2
import matplotlib.pyplot as plt
import numpy as np
import os


def hsv_split(image):
    image_hsv = cv2.cvtColor(image, cv2.COLOR_RGB2HSV)
    h, s, v = cv2.split(image_hsv)
    return h, s, v


def task1(image):
    image_hsv = cv2.cvtColor(image, cv2.COLOR_RGB2HSV)
    image_lab = cv2.cvtColor(image, cv2.COLOR_RGB2Lab)

    plt.subplot(1, 3, 1)
    plt.imshow(image)
    plt.title('RGB')

    plt.subplot(1, 3, 2)
    plt.imshow(image_hsv)
    plt.title('HSV')

    plt.subplot(1, 3, 3)
    plt.imshow(image_lab)
    plt.title('Lab')

    plt.show()

    h, s, v = hsv_split(image)

    plt.figure(figsize=(12, 4))
    plt.subplot(1, 3, 1)
    plt.imshow(h, cmap='gray')
    plt.title('Hue')

    plt.subplot(1, 3, 2)
    plt.imshow(s, cmap='gray')
    plt.title('Saturation')

    plt.subplot(1, 3, 3)
    plt.imshow(v, cmap='gray')
    plt.title('Value')

    plt.show()


def task2(image):
    h, s, v = hsv_split(image)
    s = np.clip(s * 1.5, 0, 255).astype('uint8')  # Increase saturation by 50%
    v = np.clip(v * 1.3, 0, 255).astype('uint8')  # Increase brightness by 30%

    modified_hsv = cv2.merge([h, s, v])
    modified_rgb = cv2.cvtColor(modified_hsv, cv2.COLOR_HSV2RGB)

    plt.subplot(1, 2, 1)
    plt.imshow(image)
    plt.title('Original')

    plt.subplot(1, 2, 2)
    plt.imshow(modified_rgb)
    plt.title('Modified')

    plt.show()


def task3(image, name):
    cv2.imwrite('image.png', image)
    cv2.imwrite('image.tiff', image)
    cv2.imwrite('image.bmp', image)

    png_image = cv2.imread('image.png')
    tiff_image = cv2.imread('image.tiff')
    bmp_image = cv2.imread('image.bmp')

    print("\nJPEG size:", os.path.getsize(name))
    print("PNG size:", os.path.getsize('image.png'))
    print("TIFF size:", os.path.getsize('image.tiff'))
    print("BMP size:", os.path.getsize('image.bmp'), "\n")


def task4(image):
    red_mask = image.copy()
    red_mask[:, :, 1:] = 0  # Set green and blue channels to 0

    green_mask = image.copy()
    green_mask[:, :, [0, 2]] = 0  # Set red and blue channels to 0

    blue_mask = image.copy()
    blue_mask[:, :, :2] = 0  # Set red and green channels to 0

    plt.subplot(2, 2, 1)
    plt.imshow(image)
    plt.title('Original')

    plt.subplot(2, 2, 2)
    plt.imshow(red_mask)
    plt.title('Red Mask')

    plt.subplot(2, 2, 3)
    plt.imshow(green_mask)
    plt.title('Green Mask')

    plt.subplot(2, 2, 4)
    plt.imshow(blue_mask)
    plt.title('Blue Mask')

    plt.show()


noravank = cv2.cvtColor(cv2.imread("Noravank.jpg"), cv2.COLOR_BGR2RGB)
garni = cv2.cvtColor(cv2.imread("Garni_Temple.jpg"), cv2.COLOR_BGR2RGB)
ararat = cv2.cvtColor(cv2.imread("Mount_Ararat.jpg"), cv2.COLOR_BGR2RGB)

pictures = [noravank, ararat, garni]
for pic in pictures:
    task1(pic)
    task2(pic)
    task4(pic)

task3(noravank, "Noravank.jpg")
task3(garni, "Garni_Temple.jpg")
task3(ararat, "Mount_Ararat.jpg")