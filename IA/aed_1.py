import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# configura formato do saída
pd.set_option('display.width', 320)
pd.set_option('display.max_columns', 8)

# lê o arquivo csv
consumo  = pd.read_csv('Consumo_cerveja.csv')

# imprime 5 primeiros registros do arquivo
print(consumo.head())

# imprime 5 ultimos registros do arquivo
print(consumo.tail())

# imprime as dimensões da tabela (numero de registros, numero de colunas)
print(consumo.shape)

# verifica se existe algum registro sem valores e imprime a coluna caso tenha
for i in range(len(consumo.columns)):
    coluna = consumo.iloc[:, [i]]
    if coluna.squeeze().isna().any():
        print("Coluna: " + coluna.columns.values + " possui valores vazios")

# imprime o tipo das variáveis
print(consumo.dtypes)

# relação do consumo de alcool em datas em que a temperatura máxima excedia 30 Cº
print(consumo[consumo['Temperatura Maxima (C)'] > 30.0].sort_values(by=['Consumo de cerveja (litros)', 'Temperatura Maxima (C)'], ascending=False))

# imprime a tabela descritiva das variáveis
print(consumo.describe())

# plota um gráfico sobre o final de semana
sns.countplot(data=consumo, x="Final de Semana")
plt.show()

# plota um gráfico sobre o consumo de cerveja
plt.bar(consumo['Temperatura Maxima (C)'], consumo['Consumo de cerveja (litros)'], color="red")
plt.show()