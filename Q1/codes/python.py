import ctypes
import numpy as np
import matplotlib.pyplot as plt

# Load the shared library
lib = ctypes.CDLL('./code.so')  # Replace with the actual path to your shared library

# Define the argument and return types of the shared library function
lib.get_division_points.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)]
lib.get_division_points.restype = None

# Number of dimensions for the 3D points
DIMENSIONS = 3

# Create buffers to hold the coordinates for internal and external division points
internal = (ctypes.c_double * DIMENSIONS)()
external = (ctypes.c_double * DIMENSIONS)()

# Call the function from the shared library
lib.get_division_points(internal, external)

# Convert the ctypes arrays to numpy arrays for easier manipulation
internal_np = np.array(internal[:], dtype=np.float64)
external_np = np.array(external[:], dtype=np.float64)

# Plot the points in 3D space using matplotlib
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot the original line segment
ax.plot([1, 3], [-2, 4], [3, -5], color='black', label='Line Segment')

# Plot the internal division point
ax.scatter(internal_np[0], internal_np[1], internal_np[2], color='red', s=50, label='Internal Division')
ax.text(internal_np[0], internal_np[1], internal_np[2], f'Internal ({internal_np[0]:.2f}, {internal_np[1]:.2f}, {internal_np[2]:.2f})', color='red')

# Plot the external division point
ax.scatter(external_np[0], external_np[1], external_np[2], color='blue', s=50, label='External Division')
ax.text(external_np[0], external_np[1], external_np[2], f'External ({external_np[0]:.2f}, {external_np[1]:.2f}, {external_np[2]:.2f})', color='blue')

# Set labels and title
ax.set_title('Division of Line Segment in 3D Space')
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

# Add a legend
ax.legend()

# Display the plot
plt.show()

