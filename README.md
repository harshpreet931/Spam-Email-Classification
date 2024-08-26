![Banner Image](./bannerImg.png)

A simple yet effective C-based spam email classifier using a Naive Bayes approach.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [File Structure](#file-structure)
- [How It Works](#how-it-works)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Performance](#performance)

## Overview

This project implements a basic spam email classifier in C. It uses a Naive Bayes algorithm to categorize emails as either spam or not spam based on the words they contain.

## Features

- Train on a dataset of labeled emails
- Predict whether new emails are spam or not
- Simple and lightweight implementation in C
- Fast execution with runtime measurement

## File Structure

- `main.c`: Main program file containing the entry point and sample data
- `spam_classifier.h`: Header file with function declarations and constants
- `spam_classifier_impl.c`: Implementation of the spam classifier functions

## How It Works

1. **Training**: The classifier learns from a set of pre-labeled emails, counting the occurrences of words in spam and non-spam emails.
2. **Tokenization**: Emails are broken down into individual words (tokens).
3. **Probability Calculation**: For each word, the probability of it appearing in spam and non-spam emails is calculated.
4. **Prediction**: New emails are classified by calculating the overall probability of being spam or not spam based on the words they contain.

## Getting Started

### Prerequisites

- GCC compiler

### Compilation

<!-- Yet to write compilation procedure -->

## Performance

The classifier's performance can be evaluated based on:

1. Accuracy: Printed at the end of execution
2. Execution Time: Displayed in milliseconds