import os
import re
import sys

import matplotlib.pyplot as plt
import numpy as np


def parse_segments(file_path):
    # Read the entire content of the file
    with open(file_path, "r") as file:
        content = file.read()

    # Regular expressions to capture allocated and unallocated segments for ff and bf groups
    allocated_pattern = r"Allocated Segments = \[(.*?), \]"
    unallocated_pattern = r"Unallocated Segments = \[(.*?), \]"

    # Find all allocated and unallocated segments pairs
    allocated_segments = re.findall(allocated_pattern, content)
    unallocated_segments = re.findall(unallocated_pattern, content)

    # Create a dictionary to store the results
    parsed_data = {
        "ff": {"allocated_segments": [], "unallocated_segments": []},
        "bf": {"allocated_segments": [], "unallocated_segments": []},
    }

    # Verify if we have exactly 2 pairs (ff and bf)
    if len(allocated_segments) != 2 or len(unallocated_segments) != 2:
        raise ValueError(
            "The file does not contain exactly two sets of allocated and unallocated segments for both groups."
        )

    # Process ff group (first pair)
    parsed_data["ff"]["allocated_segments"] = [int(value, 16) for value in allocated_segments[0].split(", ")]
    parsed_data["ff"]["unallocated_segments"] = [int(value, 16) for value in unallocated_segments[0].split(", ")]

    # Process bf group (second pair)
    parsed_data["bf"]["allocated_segments"] = [int(value, 16) for value in allocated_segments[1].split(", ")]
    parsed_data["bf"]["unallocated_segments"] = [int(value, 16) for value in unallocated_segments[1].split(", ")]

    return parsed_data


def plot_histograms(data):
    fig, axs = plt.subplots(2, 2, figsize=(15, 10))

    groups = ["ff", "bf"]
    segment_types = ["allocated_segments", "unallocated_segments"]

    for i, group in enumerate(groups):
        for j, segment_type in enumerate(segment_types):
            segments = data[group][segment_type]
            mean_value = np.mean(segments)
            median_value = np.median(segments)
            min_value = np.min(segments)
            max_value = np.max(segments)
            # Print mean and median to the console
            print(
                f"{group.upper()} {segment_type.replace('_', ' ').title()} - Mean: {mean_value:.2f}, Median: {median_value:.2f}, Min: {min_value}, Max: {max_value}"
            )
            ax = axs[i, j]
            ax.hist(segments, bins=30, edgecolor="black")
            ax.set_title(f'{group.upper()} {segment_type.replace("_", " ").title()}')
            ax.set_xlabel("Value")
            ax.set_ylabel("Frequency")
            ax.axvline(mean_value, color="r", linestyle="dashed", linewidth=1, label=f"Mean: {mean_value:.2f}")
            ax.axvline(median_value, color="g", linestyle="dashed", linewidth=1, label=f"Median: {median_value:.2f}")
            ax.legend()

    plt.tight_layout()
    output_file = os.path.splitext(file_path)[0] + "_histograms.png"
    plt.savefig(output_file)
    # plt.show()


# Example usage
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <file_path>")
        sys.exit(1)

    file_path = sys.argv[1]
    parsed_segments = parse_segments(file_path)

    # Plot histograms for each list and display mean and median
    plot_histograms(parsed_segments)
