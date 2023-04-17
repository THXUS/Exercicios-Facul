import math
import pandas as pd
import matplotlib.pyplot as plt

from sklearn.preprocessing import LabelEncoder
from sklearn.preprocessing import MinMaxScaler
from sklearn.cluster import KMeans

# configura o ambiente para visualização dos dados
pd.set_option('display.width', 320)
# pd.set_option('display.max_rows', None)
pd.set_option('display.max_columns', 17)

base = pd.read_csv('dado_aed2.csv')

# imprime os dados
print(base)

# mostra as dimensões dos conjuntos de dados, temos então
print("Dimensões dos dados (Instâncias, Atributos)", base.shape)

# nota-se que no conjunto de dados temos algumas colunas sem dados
print(base.iloc[:, [12, 13, 14, 15]])

# mostra o sumário dos dados
print(base.info())

# verifique a quantidade de valores ausentes por coluna
print(base.isna().sum())

# remove as colunas que não contém valores (NaN)
base_sanitizada = base.dropna(axis=1, how='all')

# mostra novamente o sumário dos dados
print(base_sanitizada.info())

# mostra os dados
print(base_sanitizada.describe())


# imprime os rótulos das outras variáveis categóricas
print(base_sanitizada['status_type'].unique())
print(base_sanitizada['status_published'].unique())

# remove as colunas status_id e status_published
base_sanitizada_sem_status = base_sanitizada.drop(columns=['status_id', 'status_published'])

# imprime as informações
print(base_sanitizada_sem_status.info())

labelEncoder = LabelEncoder()

# transforma a categoria em um número
base_sanitizada_sem_status['status_type'] = labelEncoder.fit_transform(base_sanitizada_sem_status['status_type'])

# imprime as informçãoes
print(base_sanitizada_sem_status.info())

# imprime novamente os dados
print(base_sanitizada_sem_status)

#cria X_base para usar no método do cotovelo
X_base = base_sanitizada_sem_status

cols = X_base.columns
ms = MinMaxScaler()

X_base = ms.fit_transform(X_base)
X_base = pd.DataFrame(X_base, columns=[cols])

#imprime X_base
print(X_base)

kmeans = KMeans(n_clusters=2, n_init=10)

kmeans.fit(X=X_base)

# imprime os centroides
print(kmeans.cluster_centers_)

# imprime a inercia para o caso
print(kmeans.inertia_)


def calculate_k(data, n_cluster):
    k_means = KMeans(n_clusters=n_cluster, init='k-means++', random_state=42, n_init=10)
    k_means.fit(X=data)
    print(f'Inércia com {n_cluster}: {k_means.inertia_}')
    print(f'Centróides com {n_cluster}: {k_means.cluster_centers_}')


#calcula Kmeans para 4 clusters
calculate_k(X_base, 3)
calculate_k(X_base, 4)


def calculate_wcss(data):
    wcss = []
    for n in range(2,21):
        k_means = KMeans(n_clusters=n, init='k-means++', random_state=42, n_init=10)
        k_means.fit(X=data)
        wcss.append(k_means.inertia_)
    return wcss


def optimal_number_of_clusters(wcss):
    x1, y1 = 2, wcss[0]
    x2, y2 = 20, wcss[len(wcss)-1]

    distances = []

    for i in range(len(wcss)):
        x0 = i+2
        y0 = wcss[i]
        numerator = abs((y2-y1)*x0 - (x2-x1)*y0 + x2*y1 - y2*x1)
        denominator = math.sqrt((y2 - y1)**2 + (x2-x1)**2)
        distances.append(numerator/denominator)

    return distances.index(max(distances)) + 2


wcss = calculate_wcss(X_base)
# imprime p melhor número de clusters
print(f'Melhor nùmero de clusters (usando 20 clusters) é {optimal_number_of_clusters(wcss)}')

# aplica o método do cotovelo
plt.plot(range(2, 21), wcss)
plt.grid(visible=True)
plt.xlabel('Número de Clusters')
plt.ylabel('WCSS')

plt.show()