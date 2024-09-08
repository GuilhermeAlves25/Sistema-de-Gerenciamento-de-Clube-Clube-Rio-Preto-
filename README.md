# Sistema de Gerenciamento de Clube

**Clube Rio Preto**

## Descrição

Este é um sistema de gerenciamento para um clube, com funcionalidades para cadastrar candidatos, registrar sócios e seus dependentes, promover candidatos a sócios e listar informações de sócios e candidatos.

## Funcionalidades

- **Cadastro de Candidatos**: Adiciona novos candidatos ao sistema com informações como nome, endereço, cep, bairro, telefone e email.
- **Promoção de Candidatos**: Promove candidatos a sócios e registra a categoria e a mensalidade do novo sócio.
- **Registro de Sócios**: Adiciona sócios ao sistema e permite vincular dependentes.
- **Listagem de Candidatos e Sócios**: Exibe uma lista de candidatos e sócios e permite consultar informações detalhadas.
- **Cadastro de Dependentes**: Adiciona dependentes aos sócios registrados.

## Funções

### `cadastrarcandidato()`

Adiciona um novo candidato ao sistema. O usuário deve fornecer as seguintes informações:

- Nome
- Endereço
- CEP
- Bairro
- Número de telefone
- Email

Estas informações são armazenadas em uma estrutura de dados para candidatos.

### `promoverCandidatoParaSocio(int indiceCandidato)`

Promove um candidato a sócio. Esta função:

- Copia as informações do candidato para o vetor de sócios.
- Remove o candidato da lista de candidatos.
- Atualiza o número de sócio gerado e a quantidade de sócios e candidatos no sistema.

### `registrarsocio()`

Registra um candidato como sócio. Esta função:

- Lista os candidatos disponíveis para promoção.
- Solicita ao usuário o nome do candidato a ser promovido.
- Pergunta se deseja promover o candidato a sócio.
- Se confirmado, gera um número de sócio, solicita a categoria e as informações sobre a mensalidade.

### `cadastrardependentes()`

Adiciona dependentes a um sócio existente. O usuário deve:

- Escolher um sócio da lista de sócios registrados.
- Inserir os detalhes do dependente, como nome, email, parentesco e número do cartão do dependente.

O sócio pode ter no máximo 3 dependentes.

### `listarcandidatos()`

Lista todos os candidatos registrados e permite consultar informações detalhadas de um candidato específico. O usuário deve:

- Informar o nome do candidato para obter detalhes como endereço, CEP, bairro, telefone e email.

### `listarsocios()`

Lista todos os sócios e permite consultar informações detalhadas de um sócio específico. O usuário deve:

- Informar o nome do sócio para obter detalhes como endereço, CEP, bairro, telefone, email, número do cartão de sócio e dependentes, se houver.

### `lerData(const char *prompt, int *dia, int *mes, int *ano)`

Lê uma data no formato `dd/mm/aaaa` a partir de um prompt fornecido. Esta função é utilizada para obter a data de criação da mensalidade.

### `gerarsocio()`

Gera um número único para o cartão de sócio. Esta função:

- Gera um número aleatório de até 10 dígitos.
- Verifica se o número já existe.
- Retorna um número único para ser atribuído a um novo sócio.

## Estruturas de Dados

### Candidato

Armazena informações pessoais e de contato de um candidato.

### Sócio

Armazena informações de sócios, incluindo dependentes e mensalidades.
