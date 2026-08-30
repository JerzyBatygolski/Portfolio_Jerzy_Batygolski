"""Function for training and testing of machine learning models."""

import numpy as np
import time
from dataclasses import dataclass, field
from sklearn.base import BaseEstimator

@dataclass
class Model:
    """Class to store the results of a trained model."""
    name: str
    model: BaseEstimator
    n_scores: int
    accuracy: np.ndarray = field(init=False)
    fit_time: np.ndarray = field(init=False)
    score_time: np.ndarray = field(init=False)

    def __post_init__(self):
        """Initializes result arrays after the object is created."""
        self.accuracy = np.zeros(self.n_scores, dtype=float)
        self.fit_time = np.zeros(self.n_scores, dtype=float)
        self.score_time = np.zeros(self.n_scores, dtype=float)

def run(x_train, y_train, x_test, y_test, model):
    """Trains and tests a machine learning model.

    Args:
        x_train (numpy.ndarray): The training features.
        y_train (numpy.ndarray): The training labels.
        x_test (numpy.ndarray): The testing features.
        y_test (numpy.ndarray): The testing labels.
        model: The machine learning model to be trained and tested.

    Returns:
        float: The accuracy of the model on the test set.
        float: The time taken to fit the model.
        float: The time taken to make predictions.
    """
    start_fit_time = time.time()
    model.fit(x_train, y_train)
    end_fit_time = time.time()
    fit_time = end_fit_time - start_fit_time

    start_score_time = time.time()
    accuracy = model.score(x_test, y_test)
    end_score_time = time.time()
    score_time = end_score_time - start_score_time

    return accuracy, fit_time, score_time
