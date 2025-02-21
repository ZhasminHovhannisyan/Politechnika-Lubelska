import cv2
import numpy as np
from matplotlib import pyplot as plt

# Load the X-ray image using OpenCV
glioma_path = 'glioma.jpg'
glioma_image = cv2.imread(glioma_path, cv2.IMREAD_GRAYSCALE)

fracture_path = 'fracture.jpg'
fracture_image = cv2.imread(fracture_path, cv2.IMREAD_GRAYSCALE)

tuberculosis_path = 'tuberculosis.jpg'
tuberculosis_image = cv2.imread(tuberculosis_path, cv2.IMREAD_GRAYSCALE)


def first_task(image, name):
    # Create a histogram of pixel intensities
    plt.hist(image.ravel(), bins=256, range=(0, 256), color='black')
    # Add title and labels
    plt.title(f'{name}  Pixel Intensities')
    plt.xlabel('Pixel Intensity')
    plt.ylabel('Frequency')
    # Display the histogram
    plt.show()


def second_task(image, name):
    mean_val = np.mean(image)
    min_val = np.min(image)
    max_val = np.max(image)
    print(f'\n{name} image mean pixel intensity: {mean_val}')
    print(f'{name} image minimum pixel intensity: {min_val}')
    print(f'{name} image maximum pixel intensity: {max_val}')


def third_task(image, name):
    equalized_image = cv2.equalizeHist(image)
    # show the original and equalized images
    plt.subplot(1, 2, 1)
    plt.imshow(image, cmap='gray')
    plt.title('Original Image')
    plt.axis('off')
    plt.subplot(1, 2, 2)
    plt.imshow(equalized_image, cmap='gray')
    plt.title('Equalized Image')
    plt.axis('off')
    plt.show()

    # Create a histogram of pixel intensities
    plt.hist(equalized_image.ravel(), bins=256, range=(0, 256), color='black')
    # Add title and labels
    plt.title(f'{name} image equalized  Pixel Intensities')
    plt.xlabel('Pixel Intensity')
    plt.ylabel('Frequency')
    # Display the histogram
    plt.show()



def fourth_task(image):
    # Plot the original and filtered images
    plt.figure(figsize=(10, 8))

    # Apply Median Filtering with different window sizes
    median_filtered_3x3 = cv2.medianBlur(image, 3)  # 3x3 window
    median_filtered_5x5 = cv2.medianBlur(image, 5)  # 5x5 window
    median_filtered_7x7 = cv2.medianBlur(image, 7)  # 7x7 window

    # Original Image
    plt.subplot(2, 2, 1)
    plt.imshow(image, cmap='gray')
    plt.title('Original Image')
    plt.axis('off')

    # 3x3 Median Filtered Image
    plt.subplot(2, 2, 2)
    plt.imshow(median_filtered_3x3, cmap='gray')
    plt.title('Median Filter 3x3')
    plt.axis('off')

    # 5x5 Median Filtered Image
    plt.subplot(2, 2, 3)
    plt.imshow(median_filtered_5x5, cmap='gray')
    plt.title('Median Filter 5x5')
    plt.axis('off')

    # 7x7 Median Filtered Image
    plt.subplot(2, 2, 4)
    plt.imshow(median_filtered_7x7, cmap='gray')
    plt.title('Median Filter 7x7')
    plt.axis('off')

    plt.tight_layout()
    plt.show()


def fifth_task(image):
    # Perform Fourier Transform
    dft = cv2.dft(np.float32(image), flags=cv2.DFT_COMPLEX_OUTPUT)
    dft_shift = np.fft.fftshift(dft)  # Shift the zero frequency component to the center

    # Calculate the magnitude spectrum
    magnitude_spectrum = 20 * np.log(cv2.magnitude(dft_shift[:, :, 0], dft_shift[:, :, 1]))

    # Plot the original image and its magnitude spectrum
    plt.figure(figsize=(10, 5))

    # Original Image
    plt.subplot(1, 2, 1)
    plt.imshow(image, cmap='gray')
    plt.title('Original Image')
    plt.axis('off')

    # Magnitude Spectrum
    plt.subplot(1, 2, 2)
    plt.imshow(magnitude_spectrum, cmap='gray')
    plt.title('Magnitude Spectrum (Frequency Domain)')
    plt.axis('off')

    plt.tight_layout()
    plt.show()


def sixth_task(image, name):
    from scipy.fftpack import dct
    dct_image = dct(dct(image.T, norm='ortho').T, norm='ortho')

    # Display the DCT result
    plt.imshow(np.log(np.abs(dct_image) + 1), cmap='gray')
    plt.title(f"{name} cosine transform Image")
    plt.colorbar()
    plt.show()

















# Main

first_task(glioma_image, "Glioma")
first_task(fracture_image, "Fracture")
first_task(tuberculosis_image, "Tuberculosis")

second_task(glioma_image, "Glioma")
second_task(fracture_image, "Fracture")
second_task(tuberculosis_image, "Tuberculosis")

third_task(glioma_image, "Glioma")
third_task(fracture_image, "Fracture")
third_task(tuberculosis_image, "Tuberculosis")

fourth_task(glioma_image)
fourth_task(fracture_image)
fourth_task(tuberculosis_image)
#
fifth_task(glioma_image)
fifth_task(fracture_image)
fifth_task(tuberculosis_image)

sixth_task(glioma_image, "Glioma")
sixth_task(fracture_image, "Fracture")
sixth_task(tuberculosis_image, "Tuberculosis")