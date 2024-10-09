import numpy as np
import matplotlib.pyplot as plt

# Load the data from the file
file_path = "coordinates.txt"
points = []
mode = None

# Read the coordinates from the file
with open(file_path, 'r') as file:
    for line in file:
        if "Internal" in line:
            mode = "internal"
        elif "External" in line:
            mode = "external"
        else:
            # Append the points to respective lists
            x, y, z = map(float, line.strip().split(","))
            points.append((x, y, z, mode))

# Separate the points into internal and external divisions
internal_points = [p for p in points if p[3] == "internal"]
external_points = [p for p in points if p[3] == "external"]

# Extract the original points P and Q
P = (1, -2, 3)
Q = (3, 4, -5)

# Create figure
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')

# Plot the original line segment PQ
ax.plot([P[0], Q[0]], [P[1], Q[1]], [P[2], Q[2]], 'k-', label='Line PQ')

# Plot internal division point
internal_point = internal_points[0][:3]
ax.scatter(*internal_point, color='blue', label='Internal Point')
ax.text(*internal_point, f'Internal ({internal_point[0]:.2f},{internal_point[1]:.2f},{internal_point[2]:.2f})')

# Plot external division point
external_point = external_points[0][:3]
ax.scatter(*external_point, color='red', label='External Point')
ax.text(*external_point, f'External ({external_point[0]:.2f},{external_point[1]:.2f},{external_point[2]:.2f})')

# Annotate P and Q
ax.text(P[0], P[1], P[2], f'P(1,-2,3)', fontsize=10)
ax.text(Q[0], Q[1], Q[2], f'Q(3,4,-5)', fontsize=10)

# Labels and title
ax.set_xlabel('X-axis')
ax.set_ylabel('Y-axis')
ax.set_zlabel('Z-axis')
ax.set_title('Line Segment with Internal and External Division Points')
ax.legend()

# Show plot
plt.show()
