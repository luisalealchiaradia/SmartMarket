# SmartMarket
### Sistema de gestão de estoque e análise financeira em C

O **SmartMarket** é um projeto acadêmico desenvolvido no **1º período de Ciência da Computação da PUC Minas — campus Poços de Caldas**, em 2026.

A aplicação simula rotinas de gerenciamento de um supermercado por meio de uma interface de terminal, reunindo cadastro de produtos, movimentação de estoque, cálculo de preços e relatórios financeiros.

## Objetivo

Aplicar os fundamentos da programação em C a um contexto de negócio, transformando operações comuns de um supermercado em funcionalidades organizadas e automatizadas.

O projeto explora como o processamento de dados pode apoiar o acompanhamento de mercadorias, o planejamento de reposições e a análise de resultados.

## Funcionalidades

### Gerenciamento de produtos

- Cadastro de até **100 produtos ativos**.
- Consulta por código identificador.
- Listagem, edição e exclusão lógica de produtos.
- Organização por categorias predefinidas ou personalizadas.
- Registro de custo, preço de venda, quantidade e estoque mínimo.

### Controle de estoque

- Registro de entradas de mercadorias e saídas por venda.
- Verificação de disponibilidade antes de registrar uma venda.
- Alertas para produtos com quantidade igual ou inferior ao estoque mínimo.
- Relatório com sugestões de quantidade para reposição.

### Cálculos e relatórios financeiros

- Cálculo do preço de venda a partir do custo e de um percentual de acréscimo.
- Apuração do lucro unitário de cada produto.
- Cálculo do capital investido e do valor potencial de venda do estoque.
- Registro do lucro das vendas por mês.
- Identificação de produtos com maior preço, maior lucro unitário e maior quantidade em estoque.

### Análise de desempenho

- Consulta aos lucros acumulados nos 12 meses.
- Identificação do mês com maior lucro registrado.
- Classificação dos três meses de maior lucro com **Bubble Sort**.
- Painel gerencial com produtos ativos, total de unidades, itens em estoque crítico e indicadores financeiros.

## Aplicação em um supermercado

Em um cenário de uso real, recursos como os demonstrados pelo SmartMarket poderiam apoiar:

- **Planejamento de reposição:** identificar produtos com estoque baixo e orientar a priorização de compras.
- **Organização das mercadorias:** centralizar informações de categorias, quantidades e preços.
- **Precificação:** automatizar cálculos com base no custo e no percentual de acréscimo definido.
- **Acompanhamento financeiro:** consultar o capital aplicado no estoque e comparar os lucros registrados por mês.
- **Visão gerencial:** reunir indicadores em um único painel para facilitar a consulta.

Esses são benefícios potenciais da proposta. O SmartMarket é um **protótipo acadêmico**, sem implantação ou resultados medidos em um supermercado real.

## Tecnologias e conceitos aplicados

| Recurso | Aplicação no projeto |
|---|---|
| Linguagem C | Implementação da lógica e da interface de terminal |
| Structs | Representação dos dados de cada produto |
| Vetores | Armazenamento de produtos e lucros mensais em memória |
| Funções | Organização do programa por responsabilidades |
| Strings | Manipulação de nomes e categorias |
| Condicionais e laços | Validações, navegação e processamento dos dados |
| Busca sequencial | Localização de produtos por código |
| Bubble Sort | Ordenação dos meses por lucro |

## Como compilar e executar

É necessário ter um compilador C, como o **GCC**, instalado.

No terminal, acesse a pasta do projeto e compile o arquivo:

```bash
gcc "ProjetoAE1-SmartMarket.c" -o smartmarket
```

### Linux ou macOS

```bash
./smartmarket
```

### Windows — PowerShell

```powershell
.\smartmarket.exe
```

Se o arquivo tiver outro nome, substitua `ProjetoAE1-SmartMarket.c` pelo nome correspondente no comando de compilação.

## Exemplo de utilização

1. Acesse **Gerenciamento de Produtos** e cadastre um produto.
2. Informe código, nome, categoria, quantidade, estoque mínimo e preço de custo.
3. Defina o percentual de acréscimo para calcular o preço de venda.
4. Em **Controle de Estoque**, registre uma entrada com quantidade positiva ou uma venda com quantidade negativa.
5. Ao registrar uma venda, informe o mês para contabilizar o lucro.
6. Consulte os alertas de reposição, os relatórios e o painel gerencial.

## Escopo e limitações

- Os dados são mantidos **somente em memória** e são perdidos ao encerrar o programa.
- A capacidade é de até **100 produtos ativos simultaneamente**.
- O sistema não possui banco de dados, autenticação ou integração com caixas e pagamentos.
- Os indicadores financeiros consideram custos e preços dos produtos; não incluem despesas como impostos, salários e aluguel.
- Algumas entradas possuem validação básica.
- Na análise anual, o rótulo “Faturamento Total” exibido no terminal corresponde à soma dos **lucros registrados**, e não à receita total de vendas.

## Contexto acadêmico

Projeto desenvolvido no **1º período de Ciência da Computação da PUC Minas — campus Poços de Caldas**, em 2026, como exercício de aplicação de programação estruturada, organização de dados e construção de algoritmos para problemas de gestão.
