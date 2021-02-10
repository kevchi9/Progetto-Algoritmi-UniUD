import csv
import seaborn as sns
import pandas as pd
import math
import matplotlib.pyplot as plt


def plotta_risultati(percorsoSmart, percorsoNaive):
    # apro il file csv e creo una lista con il nome delle colonne e una con i risultati

    with open(percorsoSmart, "r", encoding='utf-8-sig') as f:
        lettore = csv.reader(f, delimiter=",")
        col_names = next(lettore)
        results = []
        for line in lettore:
            results.append(line)

    # creo un dataframe
    dataSmart = pd.DataFrame()

    dataSmart[col_names[0]] = [item[0] for item in results]

    dataSmart[col_names[1]] = [item[1] for item in results]

    dataSmart["TIME"] = pd.to_numeric(dataSmart["TIME"])

    dataSmart["N"] = pd.to_numeric(dataSmart["N"])

    # apro il file csv e creo una lista con il nome delle colonne e una con i risultati
    with open(percorsoNaive, "r", encoding='utf-8-sig') as f:
        lettore = csv.reader(f, delimiter=",")
        col_names = next(lettore)
        results = []
        for line in lettore:
            results.append(line)

    # creo  un dataframe
    data = pd.DataFrame()

    data[col_names[0]] = [item[0] for item in results]

    data[col_names[1]] = [item[1] for item in results]

    data["TIME"] = pd.to_numeric(data["TIME"])

    data["N"] = pd.to_numeric(data["N"])
    plt.figure(figsize=(20, 10))
    sns.lineplot(data.N, data.TIME)
    sns.lineplot(dataSmart.N, dataSmart.TIME)
    sns.scatterplot(data.N, data.TIME)
    sns.scatterplot(dataSmart.N, dataSmart.TIME)

    plt.title("Stima tempi")
    plt.show()


def plotta_risultati_scala_logaritmica(percorsoSmart, percorsoNaive):
    # apro il file csv e creo una lista con il nome delle colonne e una con i risultati

    with open(percorsoSmart, "r", encoding='utf-8-sig') as f:
        lettore = csv.reader(f, delimiter=",")
        col_names = next(lettore)
        results = []
        for line in lettore:
            results.append(line)

    # creo un dataframe
    dataSmart = pd.DataFrame()

    dataSmart[col_names[0]] = [item[0] for item in results]

    dataSmart[col_names[1]] = [item[1] for item in results]

    dataSmart["TIME"] = pd.to_numeric(dataSmart["TIME"])

    dataSmart["N"] = pd.to_numeric(dataSmart["N"])

    # dataSmart["TIME"]= dataSmart["TIME"].map(lambda x: math.log(x))

    # dataSmart["N"]= dataSmart["N"].map(lambda x: math.log(x))

    # apro il file csv e creo una lista con il nome delle colonne e una con i risultati
    with open(percorsoNaive, "r", encoding='utf-8-sig') as f:
        lettore = csv.reader(f, delimiter=",")
        col_names = next(lettore)
        results = []
        for line in lettore:
            results.append(line)

    # creo  un dataframe
    data = pd.DataFrame()

    data[col_names[0]] = [item[0] for item in results]

    data[col_names[1]] = [item[1] for item in results]

    data["TIME"] = pd.to_numeric(data["TIME"])

    data["N"] = pd.to_numeric(data["N"])

    # data["TIME"]= data["TIME"].map(lambda x: math.log(x))

    # data["N"]= data["N"].map(lambda x: math.log(x))

    plt.figure(figsize=(20, 10))
    ax1 = sns.lineplot(data.N, data.TIME)
    ax2 = sns.lineplot(dataSmart.N, dataSmart.TIME)

    ax1.set(xscale="log")
    ax2.set(xscale="log")

    ax1.set(yscale="log")
    ax2.set(yscale="log")

    sns.scatterplot(data.N, data.TIME)
    sns.scatterplot(dataSmart.N, dataSmart.TIME)

    plt.title("Stima tempi con scala logaritmica")
    plt.show()




