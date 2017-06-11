import numpy as np
import pandas as pd

from sklearn import ensemble, feature_extraction, preprocessing

algorithm = 'Random Forest'


def read():
    train = pd.read_csv('train.csv')
    train_labels = [int(i[-1]) - 1 for i in train.target.values]
    train = train.drop('id', axis=1)
    train = train.drop('target', axis=1)

    test = pd.read_csv('test.csv')
    test = test.drop('id', axis=1)

    return np.array(train, dtype=float), np.array(train_labels), np.array(test, dtype=float)


def write(predict):
    sample = pd.read_csv('sampleSubmission.csv')
    submission = pd.DataFrame(predict, index=sample.id.values, columns=sample.columns[1:])
    submission.to_csv(algorithm + '.csv', index_label='id')


# create arrays
train, labels, test = read()

# tfidf features
tfidf = feature_extraction.text.TfidfTransformer(smooth_idf=False)
train = tfidf.fit_transform(train).toarray()
test = tfidf.transform(test).toarray()

# encode labels
label_encode = preprocessing.LabelEncoder()
labels = label_encode.fit_transform(labels)

# train classifier
if algorithm == 'Random Forest':
    clf = ensemble.RandomForestClassifier(n_estimators=1000, verbose=2)
    clf.fit(train, labels)
    predictions = clf.predict_proba(test)

elif algorithm == 'Extra Tree':
    clf = ensemble.ExtraTreesClassifier(n_estimators=1000, verbose=2)
    clf.fit(train, labels)
    predictions = clf.predict_proba(test)

elif algorithm == 'Gradient Boosting':
    clf = ensemble.GradientBoostingClassifier(n_estimators=100, verbose=2)
    clf.fit(train, labels)
    predictions = clf.predict_proba(test)

# result
write(predictions)
