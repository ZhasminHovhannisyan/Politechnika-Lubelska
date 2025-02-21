# import cv2
# import numpy as np
# from matplotlib import pyplot as plt
#
# # Load the X-ray image using OpenCV
# glioma_path = 'HW1-06.11/glioma.jpg'
# glioma_image = cv2.imread(glioma_path, cv2.IMREAD_GRAYSCALE)
#
# fracture_path = 'HW1-06.11/fracture.jpg'
# fracture_image = cv2.imread(fracture_path, cv2.IMREAD_GRAYSCALE)
#
# tuberculosis_path = 'HW1-06.11/tuberculosis.jpg'
# tuberculosis_image = cv2.imread(tuberculosis_path, cv2.IMREAD_GRAYSCALE)
#
# """
# # Display the X-ray image
# plt.imshow(tuberculosis_image, cmap='gray')
# plt.title('Tuberculosis X-ray Image')
# plt.axis('off')  # Turn off axis
# plt.show()
# """
#
#
# """################### TASK 1 ##################"""
#
# # FIRST
# # Create a histogram of pixel intensities
# plt.hist(glioma_image.ravel(), bins=256, range=(0, 256), color='black')
# # Add title and labels
# plt.title('glioma X-ray Pixel Intensities')
# plt.xlabel('Pixel Intensity')
# plt.ylabel('Frequency')
# # Display the histogram
# plt.show()
#
#
# # SECOND
# # Create a histogram of pixel intensities
# plt.hist(fracture_image.ravel(), bins=256, range=(0, 256), color='black')
# # Add title and labels
# plt.title('Fracture X-ray Pixel Intensities')
# plt.xlabel('Pixel Intensity')
# plt.ylabel('Frequency')
# # Display the histogram
# plt.show()
#
#
# # THIRD
# # Create a histogram of pixel intensities
# plt.hist(tuberculosis_image.ravel(), bins=256, range=(0, 256), color='black')
# # Add title and labels
# plt.title('Tuberculosis X-ray Pixel Intensities')
# plt.xlabel('Pixel Intensity')
# plt.ylabel('Frequency')
# # Display the histogram
# plt.show()
#
# #
# #
# #
# # """################### TASK  2 ##################"""
# #
# # FIRST
# mean_gli_val = np.mean(glioma_image)
# min_gli_val = np.min(glioma_image)
# max_gli_val = np.max(glioma_image)
# print(f'Glioma image mean pixel intensity: {mean_gli_val}')
# print(f'Glioma image minimum pixel intensity: {min_gli_val}')
# print(f'Glioma image maximum pixel intensity: {max_gli_val}')
#
# # SECOND
# mean_frac_val = np.mean(fracture_image)
# min_frac_val = np.min(fracture_image)
# max_frac_val = np.max(fracture_image)
# print(f'Fracture image mean pixel intensity: {mean_frac_val}')
# print(f'Fracture image minimum pixel intensity: {min_frac_val}')
# print(f'Fracture image maximum pixel intensity: {max_frac_val}')
#
# # THIRD
# mean_tuber_val = np.mean(tuberculosis_image)
# min_tuber_val = np.min(tuberculosis_image)
# max_tuber_val = np.max(tuberculosis_image)
# print(f'Tuberculosis image mean pixel intensity: {mean_tuber_val}')
# print(f'Tuberculosis image minimum pixel intensity: {min_tuber_val}')
# print(f'Tuberculosis image maximum pixel intensity: {max_tuber_val}')

#
# """################### TASK  3 ##################"""
# # FIRST
# equalized_gli_image = cv2.equalizeHist(glioma_image)
# # show the original and equalized images
# plt.subplot(1, 2, 1)
# plt.imshow(glioma_image, cmap='gray')
# plt.title('Original Image')
# plt.axis('off')
# plt.subplot(1, 2, 2)
# plt.imshow(equalized_gli_image, cmap='gray')
# plt.title('Equalized Image')
# plt.axis('off')
# plt.show()
#
#
# # Create a histogram of pixel intensities
# plt.hist(equalized_gli_image.ravel(), bins=256, range=(0, 256), color='black')
# # Add title and labels
# plt.title('Glioma image equalized X-ray Pixel Intensities')
# plt.xlabel('Pixel Intensity')
# plt.ylabel('Frequency')
# # Display the histogram
# plt.show()
#
#
#
# # SECOND
# equalized_frac_image = cv2.equalizeHist(fracture_image)
# # show the original and equalized images
# plt.subplot(1, 2, 1)
# plt.imshow(tuberculosis_image, cmap='gray')
# plt.title('Original Image')
# plt.axis('off')
# plt.subplot(1, 2, 2)
# plt.imshow(equalized_frac_image, cmap='gray')
# plt.title('Equalized Image')
# plt.axis('off')
# plt.show()
#
#
# # Create a histogram of pixel intensities
# plt.hist(equalized_frac_image.ravel(), bins=256, range=(0, 256), color='black')
# # Add title and labels
# plt.title('Fraction image equalized X-ray Pixel Intensities')
# plt.xlabel('Pixel Intensity')
# plt.ylabel('Frequency')
# # Display the histogram
# plt.show()
#
#
#
#
# # THIRD
# equalized_tuber_image = cv2.equalizeHist(tuberculosis_image)
# # show the original and equalized images
# plt.subplot(1, 2, 1)
# plt.imshow(tuberculosis_image, cmap='gray')
# plt.title('Original Image')
# plt.axis('off')
# plt.subplot(1, 2, 2)
# plt.imshow(equalized_tuber_image, cmap='gray')
# plt.title('Equalized Image')
# plt.axis('off')
# plt.show()
#
#
# # Create a histogram of pixel intensities
# plt.hist(equalized_tuber_image.ravel(), bins=256, range=(0, 256), color='black')
# # Add title and labels
# plt.title('Tuberculosis image equalized X-ray Pixel Intensities')
# plt.xlabel('Pixel Intensity')
# plt.ylabel('Frequency')
# # Display the histogram
# plt.show()
#
#












# # Plot the original and filtered images
# plt.figure(figsize=(10, 8))
#
# # Original Image
# plt.subplot(2, 2, 1)
# plt.imshow(tuberculosis_image, cmap='gray')
# plt.title('Original Image')
# plt.axis('off')
#
# # 3x3 Median Filtered Image
# plt.subplot(2, 2, 2)
# plt.imshow(median_filtered_3x3, cmap='gray')
# plt.title('Median Filter 3x3')
# plt.axis('off')
#
# # 5x5 Median Filtered Image
# plt.subplot(2, 2, 3)
# plt.imshow(median_filtered_5x5, cmap='gray')
# plt.title('Median Filter 5x5')
# plt.axis('off')
#
# # 7x7 Median Filtered Image
# plt.subplot(2, 2, 4)
# plt.imshow(median_filtered_7x7, cmap='gray')
# plt.title('Median Filter 7x7')
# plt.axis('off')
#
# plt.tight_layout()
# plt.show()
#


# """# ################ fourier transform ##################"""
#
# # Perform Fourier Transform
# dft = cv2.dft(np.float32(tuberculosis_image), flags=cv2.DFT_COMPLEX_OUTPUT)
# dft_shift = np.fft.fftshift(dft)  # Shift the zero frequency component to the center
#
# # Calculate the magnitude spectrum
# magnitude_spectrum = 20 * np.log(cv2.magnitude(dft_shift[:, :, 0], dft_shift[:, :, 1]))
#
# # Plot the original image and its magnitude spectrum
# plt.figure(figsize=(10, 5))
#
# # Original Image
# plt.subplot(1, 2, 1)
# plt.imshow(tuberculosis_image, cmap='gray')
# plt.title('Original Image')
# plt.axis('off')
#
# # Magnitude Spectrum
# plt.subplot(1, 2, 2)
# plt.imshow(magnitude_spectrum, cmap='gray')
# plt.title('Magnitude Spectrum (Frequency Domain)')
# plt.axis('off')
#
# plt.tight_layout()
# plt.show()
#
# """
# # reconstruct image back from FFT
# # Inverse DFT
# idft_shift = np.fft.ifftshift(dft_shift)  # Shift back the zero frequency component
# image_reconstructed = cv2.idft(idft_shift)
# image_reconstructed = cv2.magnitude(image_reconstructed[:, :, 0], image_reconstructed[:, :, 1])
#
# # Display the reconstructed image
# plt.imshow(image_reconstructed, cmap='gray')
# plt.title('Reconstructed Image from Inverse DFT')
# plt.axis('off')
# plt.show()
# """
#
