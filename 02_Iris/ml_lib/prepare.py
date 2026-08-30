"""Functions for preparing data for machine learning models."""

import numpy as np

def extract_class_names(data, separator, index):
    """Extracts class names from the dataset in order of their first occurrence.

    Args:
        data (list): A list of data points, where each data point is a string
                     containing features and a class label.
        separator (str): The separator used to split features and label.
        index (int): The index of the class column.

    Returns:
        list: A list of unique class names extracted from the dataset in
              order of their first occurrence.
    """
    class_names = []

    for sample in data:
        class_name = sample.split(separator)[index]
        if class_name not in class_names:
            class_names.append(class_name)   
     
    return class_names

def extract_features(data, separator, indices, dtype):
    """Extracts features from the dataset.

    Args:
        data (list): A list of data points, where each data point is a string
                     containing features and a class label.
        separator (str): The separator used to split features and label.
        indices (list): A list of indices for the feature columns to extract.
        dtype (type): The data type to which the extracted features should be
                     converted (e.g., float, int).

    Returns:
        numpy.ndarray: A 2D array of extracted features.
    """
    features = []

    for sample in data:
        feature_values = [dtype(sample.split(separator)[i]) for i in indices]
        features.append(feature_values)
    
    return np.array(features)

def extract_labels(data, separator, index):
    """Extracts labels from the dataset and converts them to numeric indices.

    Args:
        data (list): A list of data points, where each data point is a string
                     containing features and a class label.
        separator (str): The separator used to split features and label.
        index (int): The index of the class column.

    Returns:
        numpy.ndarray: A 1D array of numeric indices representing the extracted labels.
    """
    class_names = extract_class_names(data, separator, index)
    labels = [class_names.index(sample.split(separator)[index]) for sample in data]
    return np.array(labels)

def shuffle_dataset(x, y):
    """Shuffles the dataset.

    Args:
        x (numpy.ndarray): The features.
        y (numpy.ndarray): The labels.

    Returns:
        tuple: A tuple containing the shuffled features and labels.
    """
    i = np.argsort(np.random.random(y.shape))
    return x[i], y[i]

def train_test_split(x, y, split_ratio):
    """Splits the dataset into training and testing sets according to the specified ratio.

    Args:
        x (numpy.ndarray): The features.
        y (numpy.ndarray): The labels.
        split_ratio (float): The ratio of the dataset to be used for training.

    Returns:
        tuple: A tuple containing the training features, training labels,
               testing features, and testing labels.
    """
    split_index = int(len(y) * split_ratio)
    x_train, x_test = x[:split_index], x[split_index:]
    y_train, y_test = y[:split_index], y[split_index:]
    return x_train, y_train, x_test, y_test

def train_test_split_cv(x, y, split_index, n_splits):
    """Splits the dataset into training and testing sets for cross-validation.

    Args:
        x (numpy.ndarray): The features.
        y (numpy.ndarray): The labels.
        split_index (int): The index of the current split.
        n_splits (int): The total number of splits.
    
    Returns:
        tuple: A tuple containing the training features, training labels,
               testing features, and testing labels for the current split.
    """
    split_size = int(len(y) / n_splits)
    start_index = split_index * split_size
    end_index = start_index + split_size

    x_test = x[start_index:end_index]
    y_test = y[start_index:end_index]

    x_train = np.concatenate((x[:start_index], x[end_index:]), axis=0)
    y_train = np.concatenate((y[:start_index], y[end_index:]), axis=0)

    return x_train, y_train, x_test, y_test