import cv2
import numpy as np
from matplotlib import pyplot as plt

# Path to the uploaded image
gunshot_path = "gunshot.png"
gallstones_path = "gallstones.png"
screws_path = "screws.png"
# Load the image using PIL
gunshot_image = cv2.imread(gunshot_path)
gallstones_image = cv2.imread(gallstones_path)
screws_image = cv2.imread(screws_path)
# Convert the image to grayscale
gunshot_gray = cv2.cvtColor(np.array(gunshot_image), cv2.COLOR_RGB2GRAY)
gallstones_gray = cv2.cvtColor(np.array(gallstones_image), cv2.COLOR_RGB2GRAY)
screws_gray = cv2.cvtColor(np.array(screws_image), cv2.COLOR_RGB2GRAY)


def display_two_plots(image1, name1, image2, name2):
    plt.subplot(1, 2, 1)
    plt.imshow(image1, cmap="gray")
    plt.title(name1)
    plt.axis("off")
    plt.subplot(1, 2, 2)
    plt.imshow(image2, cmap="gray")
    plt.title(name2)
    plt.axis("off")
    plt.tight_layout()
    plt.show()


def display_four_plots(tlt, plot):
    plt.figure(figsize=(10, 8))
    for i, (img, title) in enumerate(zip(plot, tlt)):
        plt.subplot(2, 2, i + 1)
        plt.imshow(img, cmap='gray')
        plt.title(title)
        plt.axis('off')
    plt.tight_layout()
    plt.show()


def display_six_plots(denoised_images):
    titles = ["Original Noisy Image", "Median Filter 3 x 3 ", "Median Filter 5 x 5 ",
              "Median Filter 7 x 7 ", "Bilateral Filter", "Adaptive Mean Filter"]
    plt.figure(figsize=(10, 8))
    for i, (img, title) in enumerate(zip(denoised_images, titles)):
        plt.subplot(2, 3, i + 1)
        plt.imshow(img, cmap='gray')
        plt.title(title)
        plt.axis('off')
    plt.tight_layout()
    plt.show()


# GUNSHOT EDGE DETECTION
# def Canny_edge_detection(image):
#     # Perform Canny edge detection
#     image_edges = cv2.Canny(image, threshold1=50, threshold2=150)
#     # Display the original grayscale image and the edge-detected result
#     display_two_plots(image, "Grayscale Image", image_edges, "Edge Detection (Canny)")
#
#
# # passing the gunshot image to the function
# Canny_edge_detection(gunshot_gray)
#
#
# # GALLSTONES EDGE DETECTION
# def Sobel_edge_detection(image):
#     sobel_x = cv2.Sobel(image, cv2.CV_64F, 1, 0, ksize=3)  # Gradient in X direction
#     sobel_y = cv2.Sobel(image, cv2.CV_64F, 0, 1, ksize=3)  # Gradient in Y direction
#     sobel_combined = cv2.magnitude(sobel_x, sobel_y)  # Combine gradients
#     # Normalize and convert to uint8
#     sobel_combined = cv2.convertScaleAbs(sobel_combined)
#     display_two_plots(image, "Grayscale Image", sobel_combined, "Edge Detection (Sobel)")
#
#
# # passing the gallstones image to the function
# Sobel_edge_detection(gallstones_gray)
# Sobel_edge_detection(screws_gray)


# K-MEANS SEGMENTATION

def segmentation(input_image, k):
    def kmeans_segmentation(image, n=3):
        # Flatten the image for clustering
        pixel_values = image.reshape((-1, 1))
        pixel_values = np.float32(pixel_values)

        # Define criteria and apply k-means
        criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 100, 0.2)
        _, labels, centers = cv2.kmeans(pixel_values, n, None, criteria, 10, cv2.KMEANS_RANDOM_CENTERS)
        centers = np.uint8(centers)
        segmented_image = centers[labels.flatten()]
        segmented_image = segmented_image.reshape(image.shape)
        return segmented_image

    # Apply K-Means with 3 clusters
    kmeans_segmented = kmeans_segmentation(input_image, n=k)

    # Display the K-Means segmentation result
    plt.figure(figsize=(6, 6))
    plt.imshow(kmeans_segmented, cmap='gray')
    plt.title(f"K-Means Segmentation (k={k})")
    plt.axis("off")
    plt.show()

#
# # passing the images to the function
# segmentation(gunshot_gray, 3)
# segmentation(gallstones_gray, 5)
# segmentation(screws_gray, 7)


# MORPHOLOGICAL CHANGES
def morphological_changes(image):
    # Threshold the image to binary (required for morphological operations)
    _, binary_image = cv2.threshold(image, 127, 255, cv2.THRESH_BINARY)

    # Create a structuring element (kernel) for morphology
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))

    # Apply morphological transformations
    erosion = cv2.erode(binary_image, kernel, iterations=1)
    dilation = cv2.dilate(binary_image, kernel, iterations=1)
    opening = cv2.morphologyEx(binary_image, cv2.MORPH_OPEN, kernel)
    closing = cv2.morphologyEx(binary_image, cv2.MORPH_CLOSE, kernel)
    skeleton = cv2.ximgproc.thinning(binary_image)

    # Display results
    titles = ['Original Image', 'Erosion', 'Dilation', 'Opening', 'Closing', 'Skeleton']
    images = [binary_image, erosion, dilation, opening, closing, skeleton]

    plt.figure(figsize=(12, 8))
    for i in range(6):
        plt.subplot(2, 3, i + 1)
        plt.imshow(images[i], cmap='gray')
        plt.title(titles[i])
        plt.axis('off')
    plt.tight_layout()
    plt.show()


morphological_changes(gunshot_gray)
morphological_changes(gallstones_gray)
morphological_changes(screws_gray)


# ADD SALT AND PEPPER NOISE


def add_salt_and_pepper_noise(image, noise_level):
    noisy_image = image.copy()
    total_pixels = image.size
    num_salt = int(noise_level * total_pixels / 2)  # Half for salt
    num_pepper = int(noise_level * total_pixels / 2)  # Half for pepper

    # Add salt (white pixels)
    salt_coords = [np.random.randint(0, i - 1, num_salt) for i in image.shape]
    noisy_image[salt_coords[0], salt_coords[1]] = 255

    # Add pepper (black pixels)
    pepper_coords = [np.random.randint(0, i - 1, num_pepper) for i in image.shape]
    noisy_image[pepper_coords[0], pepper_coords[1]] = 0

    return noisy_image


def plot_salt_and_pepper_images(image):
    # Add noise at three levels
    noise_levels = [0.05, 0.1, 0.2]  # Low, medium, and high noise levels
    noisy_images = [add_salt_and_pepper_noise(image, level) for level in noise_levels]

    # Display the results
    titles = ["Original Image", "5% Noise", "10% Noise", "20% Noise"]
    images = [image] + noisy_images

    plt.figure(figsize=(10, 8))
    for i, (img, title) in enumerate(zip(images, titles)):
        plt.subplot(2, 2, i + 1)
        plt.imshow(img, cmap='gray')
        plt.title(title)
        plt.axis('off')
    plt.tight_layout()
    plt.show()

    return noisy_images


gunshot_salt_and_pepper = plot_salt_and_pepper_images(gunshot_gray)
gallstones_salt_and_pepper = plot_salt_and_pepper_images(gallstones_gray)
screws_salt_and_pepper = plot_salt_and_pepper_images(screws_gray)


# REMOVE SALT AND PEPPER NOISE


def first_denoise1(image):
    median_denoised1 = cv2.medianBlur(image, 3)
    median_denoised2 = cv2.medianBlur(image, 5)
    median_denoised3 = cv2.medianBlur(image, 7)
    bilateral_denoised = cv2.bilateralFilter(image, 9, 75, 75)
    kernel = np.ones((3, 3), np.float32) / (3 ** 2)
    adaptive_mean_denoised = cv2.filter2D(image, -1, kernel)

    return median_denoised1, median_denoised2, median_denoised3, bilateral_denoised, adaptive_mean_denoised


gun_med_denoised1, gun_med_denoised2, gun_med_denoised3, gun_bilat_denoised, \
    gun_adaptive_denoised = first_denoise1(gunshot_salt_and_pepper[2])

gallstones_med_denoised1, gallstones_med_denoised2, gallstones_med_denoised3, \
    gallstones_bilat_denoised, gallstones_adaptive_denoised = first_denoise1(gallstones_salt_and_pepper[2])

screws_med_denoised1, screws_med_denoised2, screws_med_denoised3, \
    screws_bilat_denoised, screws_adaptive_denoised = first_denoise1(screws_salt_and_pepper[2])

gunshot_median_plot = [gunshot_salt_and_pepper[2], gun_med_denoised1,
                       gun_med_denoised2, gun_med_denoised3]
gallstones_median_plot = [gallstones_salt_and_pepper[2], gallstones_med_denoised1,
                          gallstones_med_denoised2, gallstones_med_denoised3]
screws_median_plot = [screws_salt_and_pepper[2], screws_med_denoised1,
                      screws_med_denoised2, screws_med_denoised3]

median_filter_titles = ["Original Noisy Image", "Median Filter 3 x 3 ", "Median Filter 5 x 5 ", "Median Filter 7 x 7 "]

display_four_plots(median_filter_titles, gunshot_median_plot)
display_two_plots(gunshot_salt_and_pepper[2], "Noisy Image", gun_bilat_denoised, "Bilateral Filter")
display_two_plots(gunshot_salt_and_pepper[2], "Noisy Image", gun_adaptive_denoised, "Adaptive Mean Filter")

display_four_plots(median_filter_titles, gallstones_median_plot)
display_two_plots(gallstones_salt_and_pepper[2], "Noisy Image", gallstones_bilat_denoised, "Bilateral Filter")
display_two_plots(gallstones_salt_and_pepper[2], "Noisy Image", gallstones_adaptive_denoised, "Adaptive Mean Filter")

display_four_plots(median_filter_titles, screws_median_plot)
display_two_plots(screws_salt_and_pepper[2], "Noisy Image", screws_bilat_denoised, "Bilateral Filter")
display_two_plots(screws_salt_and_pepper[2], "Noisy Image", screws_adaptive_denoised, "Adaptive Mean Filter")

# Display the results of comparison
gunshot_sap_comparison = [gunshot_salt_and_pepper[2], gun_med_denoised1,
                          gun_med_denoised2, gun_med_denoised3,
                          gun_bilat_denoised, gun_adaptive_denoised]

gallstones_sap_comparison = [gallstones_salt_and_pepper[2], gallstones_med_denoised1,
                             gallstones_med_denoised2, gallstones_med_denoised3,
                             gallstones_bilat_denoised, gallstones_adaptive_denoised]

screws_sap_comparison = [screws_salt_and_pepper[2], screws_med_denoised1,
                         screws_med_denoised2, screws_med_denoised3,
                         screws_bilat_denoised, screws_adaptive_denoised]

display_six_plots(gunshot_sap_comparison)
display_six_plots(gallstones_sap_comparison)
display_six_plots(screws_sap_comparison)


# GAUSSIAN NOISE
def add_gaussian_noise(image, mean, variance):
    image_float = image.astype(np.float32)
    sigma = variance ** 0.5
    gaussian_noise = np.random.normal(mean, sigma, image.shape)
    noisy_image = image_float + gaussian_noise
    # Clip the values to ensure they remain valid
    noisy_image = np.clip(noisy_image, 0, 255).astype(np.uint8)
    return noisy_image


def plot_gaussian_noise(image):
    # Add Gaussian noise at three levels
    noise_levels = [
        (0, 10),  # Low noise: Mean=0, Variance=10
        (0, 50),  # Medium noise: Mean=0, Variance=50
        (0, 100)  # High noise: Mean=0, Variance=100
    ]
    noisy_images = [add_gaussian_noise(image, mean, variance) for mean, variance in noise_levels]

    # Display the results
    titles = ["Original Image", "Low Noise (Var=10)", "Medium Noise (Var=50)", "High Noise (Var=100)"]
    images = [image] + noisy_images

    plt.figure(figsize=(10, 8))
    for i, (img, title) in enumerate(zip(images, titles)):
        plt.subplot(2, 2, i + 1)
        plt.imshow(img, cmap='gray')
        plt.title(title)
        plt.axis('off')
    plt.tight_layout()
    plt.show()
    return noisy_images


gunshot_gaussian_noise = plot_gaussian_noise(gunshot_gray)
gallstones_gaussian_noise = plot_gaussian_noise(gallstones_gray)
screws_gaussian_noise = plot_gaussian_noise(screws_gray)


# REMOVE GAUSSIAN NOISE
def first_denoise2(image):
    # Apply GaussianBlur
    gaussian_denoised = cv2.GaussianBlur(image, (7, 7), 1.5)

    # Apply Non-Local Means (NLM) Denoising
    nlm_denoised = cv2.fastNlMeansDenoising(image, h=15, templateWindowSize=7, searchWindowSize=21)

    # Apply bilateral Filtering as a last resort for mixed noise
    bilateral_denoised = cv2.bilateralFilter(image, 9, 75, 75)
    return gaussian_denoised, nlm_denoised, bilateral_denoised


gunshot_gaussian_denoised, gunshot_nlm_denoised, gaussian_bilateral_denoised = first_denoise2(gunshot_gaussian_noise[2])
display_two_plots(gunshot_gaussian_noise[2], "Noisy image", gunshot_gaussian_denoised, "Gaussian Blurring")
display_two_plots(gunshot_gaussian_noise[2], "Noisy image", gunshot_nlm_denoised, "Non-Local Means")
display_two_plots(gunshot_gaussian_noise[2], "Noisy image", gaussian_bilateral_denoised, "Bilateral Filtering")

# Display the results
second_titles = ["Original Noisy Image", "Gaussian Blurring", "Non-Local Means", "Bilateral Filtering"]
gunshot_denoised2_images = [gunshot_gaussian_noise[2], gunshot_gaussian_denoised, gunshot_nlm_denoised,
                            gaussian_bilateral_denoised]

display_four_plots(second_titles, gunshot_denoised2_images)

gallstones_gaussian_denoised, gallstones_nlm_denoised, gaussian_bilateral_denoised = first_denoise2(
    gallstones_gaussian_noise[2])
display_two_plots(gallstones_gaussian_noise[2], "Noisy image", gallstones_gaussian_denoised, "Gaussian Blurring")
display_two_plots(gallstones_gaussian_noise[2], "Noisy image", gallstones_nlm_denoised, "Non-Local Means")
display_two_plots(gallstones_gaussian_noise[2], "Noisy image", gaussian_bilateral_denoised, "Bilateral Filtering")

# Display the results
gallstones_denoised2_images = [gallstones_gaussian_noise[2], gallstones_gaussian_denoised, gallstones_nlm_denoised,
                               gaussian_bilateral_denoised]

screws_gaussian_denoised, screws_nlm_denoised, gaussian_bilateral_denoised = first_denoise2(
    screws_gaussian_noise[2])
display_two_plots(screws_gaussian_noise[2], "Noisy image", screws_gaussian_denoised, "Gaussian Blurring")
display_two_plots(screws_gaussian_noise[2], "Noisy image", screws_nlm_denoised, "Non-Local Means")
display_two_plots(screws_gaussian_noise[2], "Noisy image", gaussian_bilateral_denoised, "Bilateral Filtering")

# Display the results
screws_denoised2_images = [screws_gaussian_noise[2], screws_gaussian_denoised, screws_nlm_denoised,
                           gaussian_bilateral_denoised]


def plot_gaussian_conclusion(image_list):
    plt.figure(figsize=(10, 8))
    for i, (img, title) in enumerate(zip(image_list, second_titles)):
        plt.subplot(2, 2, i + 1)
        plt.imshow(img, cmap='gray')
        plt.title(title)
        plt.axis('off')
    plt.tight_layout()
    plt.show()


plot_gaussian_conclusion(gunshot_denoised2_images)
plot_gaussian_conclusion(gallstones_denoised2_images)
plot_gaussian_conclusion(screws_denoised2_images)
