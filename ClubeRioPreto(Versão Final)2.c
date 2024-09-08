#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define Max 3

void listarcandidatos();
void cadastrarcandidato();
void registrarsocio();
long gerarsocio();
int qtdcandidatos = 0;
void listarsocios();
int qtdsocios=0;
void cadastrardependentes();
void consultarmensalidade();
double calcularjuros();
void quitarmensalidade();


void lerData();
typedef struct{
	int dia;
	int mes;
	int ano;
}data;

typedef struct{
	int dia;
	int mes;
	int ano;
}dataP;

typedef struct{
	data Data;
	double valor;
	dataP Datap;
	double juros;
	double valorP;
	int MensalidadeQ;
	int diasTotais;
	
}Mensalidade;


typedef struct{
	char parentesco[50];
	char nomeDependente[50];
	long cartaoDependente;
	char emailDependente[50];
	
}Dependente;

typedef struct {
    char endereco[100];
    char cep[100];
    char bairro[100];
} Localizacao;

typedef struct {
    char telefone[15];
    char email[50];
} Contato;


typedef struct {
    char nomeCandidato[50];
    Localizacao localizacao;
    Contato contato;
    long numeroSocio;
    Dependente dependente[Max];
    int qtdDependentes;
    char categoria;
    Mensalidade mensalidade[Max];
    int qtdmensal;
    
} Candidato;

Candidato socios[Max];

Candidato candidatos[Max];

int main() {
    int escolha;
    int x = 1;
    setlocale(LC_ALL, "Portuguese");
    
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    while (x) {
        printf("\n\t====Bem vindo ao sistema de gerenciamento do clube Rio Preto====\n\n");
        printf("\tDigite o numero das opcoes disponiveis abaixo:\n");
        printf("\t-----------------------------------------\n");
        printf("\t1. Registrar candidato\n");
        printf("\t2. Consultar candidato:\n");
        printf("\t3. Registrar socio\n");
        printf("\t4. Consultar socio\n");
        printf("\t5. Registrar dependente\n");
        printf("\t6. Consultar mensalidade\n");
        printf("\t7. Sair do sistema\n");
        printf("\t-----------------------------------------\n");
        scanf("\t%d", &escolha);
        getchar(); // Limpa o newline deixado pelo scanf

        switch (escolha) {
            case 1:
                cadastrarcandidato();
                break;
            case 2:
                listarcandidatos();
                break;
            case 3:
                registrarsocio();
                break;
            case 4:
                listarsocios();
                break;
            case 5:
                cadastrardependentes();
                break;
            case 6:
            	consultarmensalidade();
            	break;
            case 7:
            	printf("Programa encerrado!\n");
                x = 0;
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    }
    return 0;
}

void quitarmensalidade(int i,int M){//o i representa a posição do socio. o M a mensalidade que esta sendo quitada
	float valor;
	
	
	lerData("Digite a data de pagamento (dd/mm/aaaa): ", 
                        &socios[i].mensalidade[M].Datap.dia, 
                        &socios[i].mensalidade[M].Datap.mes, 
                        &socios[i].mensalidade[M].Datap.ano);
   
    calcularjuros(i,M);
	
                        
	printf("\t---Dados da mensalidade---\n");
	printf("\t-----------------------------------------\n");
	printf("\tValor da mensalidade: %.2lf\n",socios[i].mensalidade[M].valor);
	printf("\tData de criação da mensalidade: %d/%d/%d\n",socios[i].mensalidade[M].Data.dia,socios[i].mensalidade[M].Data.mes,socios[i].mensalidade[M].Data.ano);
	printf("\tJuros da mensalidade: %.2lf%%\n",socios[i].mensalidade[M].juros);
    printf("\t-----------------------------------------\n\n");
    if(socios[i].mensalidade[M].juros>0){    
	printf("\tValor a ser pago com juros de %.2lf%%: %.2lf\n\n",socios[i].mensalidade[M].juros,socios[i].mensalidade[M].valor+(socios[i].mensalidade[M].valor*socios[i].mensalidade[M].juros));
	valor = socios[i].mensalidade[M].valor+(socios[i].mensalidade[M].valor*socios[i].mensalidade[M].juros);
	}else{
		printf("\tValor a ser pago: %.2lf\n",socios[i].mensalidade[M].valor);
		valor = socios[i].mensalidade[M].valor;
	}
    printf("\tDeseja quitar a mensalidade acima?\n1.Sim\n2.Não\n\n");
    int op;
    scanf("%d",&op);
    getchar();
    if(op == 1){
    	socios[i].mensalidade[M].valorP = valor;
    	printf("\t====Mensaliade quitada com sucesso====\n\n");
    	printf("\tValor pago: %.2lf\n\n",valor);
    	printf("\tMensalidade atualizada!\n\n");
	}
}


double calcularjuros(int indice,int M){//indice = posição do socio, M = qual mensalidade esta manipulando
	
	int qtd = socios[indice].qtdmensal;
	
	int data1 = socios[indice].mensalidade[M].Data.dia + (socios[indice].mensalidade[M].Data.mes * 30) + (socios[indice].mensalidade[M].Data.ano * 365);
    int data2 = socios[indice].mensalidade[M].Datap.dia + (socios[indice].mensalidade[M].Datap.mes * 30) +  (socios[indice].mensalidade[M].Datap.ano * 365);
    
    socios[indice].mensalidade[M].diasTotais = data2 - data1;
    socios[indice].mensalidade[M].juros = (socios[indice].mensalidade[M].diasTotais/30.0) * 0.10;
	
	return socios[indice].mensalidade[M].juros;

}

void consultarmensalidade(){
	
	int i;
    char es[50];
    int encontrado = 0;
    int numero; //variavel responsavel por definir qual mensalidade estamos manipulando
    
    if(qtdsocios == 0){
    	printf("\t====Nenhum socio cadastrado no sistema====\n\n");
    	return;
	}
    
	printf("\t~~~~~~~~Socios~~~~~~~~\n");
	printf("\t-------------------------------------\n");
	for(i=0;i<qtdsocios;i++){
		printf("\t>%s\n",socios[i].nomeCandidato);	
		}
	printf("\t-------------------------------------\n");
	
	printf("\tDigite o nome de um dos socios acima que deseja consultar a mensalidade:\n");
	fgets(es, sizeof(es), stdin);
    es[strcspn(es, "\n")] = '\0';
	
	int indice=-1;
	int j;
	int qtd;
	for(i=0;i<qtdsocios;i++){
		if (strcasecmp(socios[i].nomeCandidato, es) == 0){
		encontrado = 1;
		indice = i;
		qtd = socios[i].qtdmensal;
		break;
	}
}
		printf("\n\n\t~~~~~~Socio encontrado~~~~~~\n\n");
		printf("\t---Mensalidades---\n");
		for(j=0;j<socios[indice].qtdmensal;j++){
		printf("\tMensalidade %d\n",j+1);
		printf("\t-----------------------------------------\n");
		printf("\tData de criação da mensalidade: %d/%d/%d\n",socios[indice].mensalidade[j].Data.dia,socios[indice].mensalidade[j].Data.mes,socios[indice].mensalidade[j].Data.ano);
		printf("\tValor da mensalidade: %.2lf\n",socios[indice].mensalidade[j].valor);
		if(socios[i].mensalidade[j].valorP>0){
	    printf("\tValor pago: %.2lf\n\n",socios[indice].mensalidade[j].valorP);
	    printf("\tData de pagamento da mensalidade: %d/%d/%d\n",socios[indice].mensalidade[j].Datap.dia,socios[indice].mensalidade[j].Datap.mes,socios[indice].mensalidade[j].Datap.ano);
	    printf("\tMensalidade quitada: sim\n");
	    printf("\t-----------------------------------------\n\n");
		}else{
		 printf("\tMensalidade pendente!\n\n");
		 printf("\t-----------------------------------------\n\n");
		}
			}
			
		
		printf("\t----Digite a opção abaixo referente a mensalidade:\n\n");
		printf("\t------------------------------------------\n");
		printf("\t1.Calcular Juros\n");
		printf("\t2.Quitar mensalidade\n");
		printf("\t3.Registrar nova mensalidade\n");
		printf("\t4.Cancelar\n");
		printf("\t------------------------------------------\n");
		int op;
		scanf("%d",&op);
		getchar();
		switch(op){
			case 1: 	
						printf("Digite o numero da mensalidade que deseja calcular os juros:\n\n");
						scanf("%d",&numero);
						getchar();
						numero -= 1;
						
						lerData("\tDigite a data de pagamento (dd/mm/aaaa): \n\n", 
                        &socios[indice].mensalidade[numero].Datap.dia, 
                        &socios[indice].mensalidade[numero].Datap.mes, 
                        &socios[indice].mensalidade[numero].Datap.ano);
                    	
                    	calcularjuros(indice,numero);
                    	
                    	printf("\t====Juros====\n");
                    	printf("\t------------------------------------------\n");
                    	printf("\tJuros da mensalidade: %.2lf%%\n",socios[indice].mensalidade[numero].juros);
                    	printf("\tValor da mensalidade com juros de %.2lf%%: %.2lf\n\n",socios[indice].mensalidade[numero].juros,socios[indice].mensalidade[numero].valor+(socios[indice].mensalidade[numero].valor*socios[indice].mensalidade[numero].juros));
                        printf("\t------------------------------------------\n");
						printf("\tDeseja quitar a mensalidade?\n1.Sim\n2.Não\n\n");
                        scanf("%d",&op);
                        if(op == 1){
                        	quitarmensalidade(indice,numero);
						}
						break;
                        
            case 2:
            			printf("Digite o numero da mensalidade que deseja quitar:\n\n");
						scanf("%d",&numero);
						getchar();
						numero -= 1;
						
						if(socios[indice].mensalidade[numero].valorP<1){
							
							
							
						    
							quitarmensalidade(indice,numero);
						}else{
							printf("\t==A mensalidade que vc digitou ja foi quitada!!==\n\n");
						}
            			
            			break;
            	
        	case 3:
        	
        	if(socios[indice].qtdmensal == Max){
        		printf("\tMaximo de mensalidades cadastradas para esse socio===\n\n");
        		return;
			}
        		
        		lerData("Digite a data de criação da mensalidade (dd/mm/aaaa): ",
                        &socios[indice].mensalidade[qtd].Data.dia, 
                        &socios[indice].mensalidade[qtd].Data.mes, 
                        &socios[indice].mensalidade[qtd].Data.ano);
                        
                        
                        printf("Digite o valor da mensalidade:\n");
                    	scanf("%lf",&socios[indice].mensalidade[qtd].valor);
                    	
                    	printf("\t===Nova Mensalidade criada===\n\n");
                    	
                    	socios[indice].qtdmensal++;
            case 4:
            	printf("\t===Operação cancelada===");
            	break;
        		
		}
	
		
		if(!encontrado){
			printf("\t====Socio não encontrado====\n");
			return;
		}
		printf("\tpressione qualquer tecla para retornar ao menu inicial\n\n");
		getchar();
}

void cadastrardependentes(){
	
	int i;
    char es[50];
    int encontrado = 0;
    
    
    
    if(qtdsocios == 0){
    	printf("\t====Nenhum socio cadastrado====\n");
    	return;
	}
    
	printf("\t~~~~~~~~Lista de socios:~~~~~~~~\n");
	printf("\t-------------------------------------\n");
	for(i=0;i<qtdsocios;i++){
	printf("\t>%s\n",socios[i].nomeCandidato);
	}
	printf("\t-------------------------------------\n");
	
	printf("\tDigite o nome do socio acima o qual deseja vincular um dependente:\n");
	fgets(es, sizeof(es), stdin);
    es[strcspn(es, "\n")] = '\0';
    
    for(i=0;i<qtdsocios;i++){
	if (strcasecmp(socios[i].nomeCandidato, es) == 0) {
                printf("\n\n\t!!Socio encontrado!!\n\n");
                if(socios[i].qtdDependentes > Max){
                	printf("\t====O socio digitado ja possui o maximo de dependentes (3)====\n\n");
                	return;
                	break;
				}
            encontrado = 1;
            

        	
        	int qtdD = socios[i].qtdDependentes;
        	
			printf("\tDigite o nome do dependente:\n");
    		fgets(socios[i].dependente[qtdD].nomeDependente, sizeof(socios[i].dependente[qtdD].nomeDependente), stdin);
   			socios[i].dependente[qtdD].nomeDependente[strcspn(socios[i].dependente[qtdD].nomeDependente, "\n")] = '\0'; // Remove newline
   			
   			printf("\tDigite o email do dependente:\n");
    		fgets(socios[i].dependente[qtdD].emailDependente, sizeof(socios[i].dependente[qtdD].emailDependente), stdin);
   			socios[i].dependente[qtdD].emailDependente[strcspn(socios[i].dependente[qtdD].emailDependente, "\n")] = '\0'; // Remove newline
   			
   			printf("\tDigite o parentesco do dependente com o socio:\n");
    		fgets(socios[i].dependente[qtdD].parentesco, sizeof(socios[i].dependente[qtdD].parentesco), stdin);
   			socios[i].dependente[qtdD].nomeDependente[strcspn(socios[i].dependente[qtdD].nomeDependente, "\n")] = '\0'; // Remove newline
		
			printf("\tDigite o numero do cartão dependente:\n");
    		scanf("%ld",&socios[i].dependente[qtdD].cartaoDependente);
   			
   			socios[i].qtdDependentes++;
   			printf("Dependente adicionado com sucesso!\n");
			}
	
		}

	
	
	if(!encontrado){
    printf("Socio nao encontrado!\n");
	return;
	}
	printf("\tpressione qualquer tecla para retornar ao menu inicial\n\n");
	getchar();
}

void listarcandidatos(){
	int i;
    char es[50];
    int encontrado = 0;
    
    if(qtdcandidatos == 0){
    	printf("\t====Nenhum candidato cadastrado no sistema====\n");
    	return;
	}
    
	printf("\t~~~~~~~~Candidatos a socio~~~~~~~~\n");
	printf("\t-------------------------------------\n");
	for(i=0;i<qtdcandidatos;i++){
		printf("\t>%s\n",candidatos[i].nomeCandidato);	
		}
	printf("\t-------------------------------------\n");
	
	printf("\tDigite o nome de um dos candidatos acima que deseja consultar os dados:\n");
	fgets(es, sizeof(es), stdin);
    es[strcspn(es, "\n")] = '\0';
    
	for(i=0;i<qtdcandidatos;i++){
	if (strcasecmp(candidatos[i].nomeCandidato, es) == 0) {
		printf("\n\n\t!!Candidato encontrado!!\n\n");
		encontrado = 1;
    	printf("\t-----------------------------------------\n");
        printf("\tNome: %s\n", candidatos[i].nomeCandidato);
        printf("\tEndereco: %s\n", candidatos[i].localizacao.endereco);
        printf("\tCep: %s\n", candidatos[i].localizacao.cep);
        printf("\tBairro: %s\n", candidatos[i].localizacao.bairro);
        printf("\tNumero de telefone: %s\n", candidatos[i].contato.telefone);
        printf("\tEmail: %s\n", candidatos[i].contato.email);
        printf("\t-----------------------------------------\n\n");
		}
	}
    
    if(!encontrado){
    	printf("Candidato nao encontrado!\n");
	}
	
	printf("\tpressione qualquer tecla para retornar ao menu inicial\n\n");
	getchar();
	
}


void cadastrarcandidato() {
    if (qtdcandidatos >= Max) {
        printf("Limite de candidatos alcançado.\n");
        return;
    }

    printf("Digite o nome do candidato:\n");
    fgets(candidatos[qtdcandidatos].nomeCandidato, sizeof(candidatos[qtdcandidatos].nomeCandidato), stdin);
    candidatos[qtdcandidatos].nomeCandidato[strcspn(candidatos[qtdcandidatos].nomeCandidato, "\n")] = '\0'; // Remove newline

    printf("Digite o endereco do candidato:\n");
    fgets(candidatos[qtdcandidatos].localizacao.endereco, sizeof(candidatos[qtdcandidatos].localizacao.endereco), stdin);
    candidatos[qtdcandidatos].localizacao.endereco[strcspn(candidatos[qtdcandidatos].localizacao.endereco, "\n")] = '\0'; // Remove newline

    printf("Digite o cep do candidato:\n");
    fgets(candidatos[qtdcandidatos].localizacao.cep, sizeof(candidatos[qtdcandidatos].localizacao.cep), stdin);
    candidatos[qtdcandidatos].localizacao.cep[strcspn(candidatos[qtdcandidatos].localizacao.cep, "\n")] = '\0'; // Remove newline

    printf("Digite o bairro do candidato:\n");
    fgets(candidatos[qtdcandidatos].localizacao.bairro, sizeof(candidatos[qtdcandidatos].localizacao.bairro), stdin);
    candidatos[qtdcandidatos].localizacao.bairro[strcspn(candidatos[qtdcandidatos].localizacao.bairro, "\n")] = '\0'; // Remove newline

    printf("Digite o numero de telefone do candidato:\n");
    fgets(candidatos[qtdcandidatos].contato.telefone, sizeof(candidatos[qtdcandidatos].contato.telefone), stdin);
    candidatos[qtdcandidatos].contato.telefone[strcspn(candidatos[qtdcandidatos].contato.telefone, "\n")] = '\0'; // Remove newline

    printf("Digite o email do candidato:\n");
    fgets(candidatos[qtdcandidatos].contato.email, sizeof(candidatos[qtdcandidatos].contato.email), stdin);
    candidatos[qtdcandidatos].contato.email[strcspn(candidatos[qtdcandidatos].contato.email, "\n")] = '\0'; // Remove newline

    qtdcandidatos++;
    system("cls");
    printf("\t\t\n\n~~~~~~~~~~CANDIDADO CADASTRADO COM SUCESSO~~~~~~~~~~\n\n");
}


void promoverCandidatoParaSocio(int indiceCandidato) {
	  int i;
    if (qtdsocios < Max) {
        // Copia as informações do candidato para o vetor de sócios
        socios[qtdsocios] = candidatos[indiceCandidato];
        
        // Move o candidato para o final do vetor e reduz a quantidade de candidatos
        for (i = indiceCandidato; i < qtdcandidatos - 1; i++) {
            candidatos[i] = candidatos[i + 1];
        }
        
        qtdcandidatos--;
        qtdsocios++;
    } else {
        printf("Limite de sócios alcançado.\n");
    }
}

void registrarsocio() {
    
    int i;
    char nome[50];
    int encontrado = 0;
    int disponiveis = 0;
	int qtd;
	
	if(qtdsocios > Max){
		printf("\t===Máximo de socios cadastrados no sistema===\n\n");
		return;
	}
	
	if(qtdcandidatos == 0){
		printf("\t====Nenhum candidato cadastrado no sistema====\n");
		return;
	}

    printf("\t~~~~~~Candidatos a socio disponiveis~~~~~~\n\n");
	printf("\t-----------------------------------------\n");
    for (i = 0; i < qtdcandidatos; i++) {
        printf("\t>%s\n", candidatos[i].nomeCandidato);
    }
	printf("\t-----------------------------------------\n");
	
        printf("\t-----Digite o nome do candidato acima que deseja promover a socio:-----\n");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0';

        for (i = 0; i < qtdcandidatos; i++) {
            if (strcasecmp(candidatos[i].nomeCandidato, nome) == 0) {
            	qtd = socios[i].qtdmensal;
                printf("\n\n\t!!Candidato encontrado!!\n\n");
                encontrado = 1;
                printf("\tDeseja tornar %s socio do clube?\n Digite S para torná-lo(a) sócio ou qualquer outra tecla para cancelar: \n", candidatos[i].nomeCandidato);
                char es;
                scanf(" %c", &es); // Adiciona um espaço para ignorar espaços em branco
                getchar(); // Limpa o newline deixado pelo scanf

                if (es == 's' || es == 'S') {
                    candidatos[i].numeroSocio = gerarsocio();
                    
                    promoverCandidatoParaSocio(i);
                    
                    	printf("\tDigite a categoria de %s:\nExemplo: A,B,C\n",socios[qtdsocios-1].nomeCandidato);
                    	scanf(" %c",&socios[qtdsocios-1].categoria);
                    	
                    	lerData("Digite a data de criação da mensalidade (dd/mm/aaaa): ", 
                        &socios[qtdsocios-1].mensalidade[socios[qtdsocios-1].qtdmensal].Data.dia, 
                        &socios[qtdsocios-1].mensalidade[socios[qtdsocios-1].qtdmensal].Data.mes, 
                        &socios[qtdsocios-1].mensalidade[socios[qtdsocios-1].qtdmensal].Data.ano);
                        
                        printf("Digite o valor da mensalidade:\n");
                    	scanf("%lf",&socios[qtdsocios-1].mensalidade[socios[qtdsocios-1].qtdmensal].valor);
                    	
                    	socios[qtdsocios-1].qtdmensal++;
                    	
                    	
						printf("\n\n\t----%s agora é sócio(a) do clube!----\n",socios[qtdsocios-1].nomeCandidato);
						
					}
                }
				
			
				}
               
            
        
    

    if (!encontrado) {
        printf("\t!!Candidato não encontrado!!\n");
    }
    printf("\tpressione qualquer tecla para retornar ao menu inicial\n\n");
	getchar();

}

void lerData(const char *prompt, int *dia, int *mes, int *ano) {
    printf("%s", prompt);
    while (scanf("%d/%d/%d", dia, mes, ano) != 3) {
        printf("Formato de data inválido. Tente novamente (dd/mm/aaaa): ");
        while (getchar() != '\n'); // Limpa o buffer de entrada
    }
    getchar(); // Limpa o newline restante
}

long gerarsocio() {
    static long sociosExistentes[Max] = {0}; // Array para armazenar números de sócios existentes
    static int qtdSocios = 0;
    long novoSocio;
    int i, unico;

    do {
        unico = 1;
        novoSocio = rand() % 10000000000; // Gera número de até 10 dígitos

        // Verifica se o número gerado já existe
        for (i = 0; i < qtdSocios; i++) {
            if (sociosExistentes[i] == novoSocio) {
                unico = 0;
                break;
            }
        }
    } while (!unico);

    // Adiciona o novo número de sócio ao array de sócios existentes
    if (qtdSocios < Max) {
        sociosExistentes[qtdSocios] = novoSocio;
        qtdSocios++;
    }

    return novoSocio;
}

void listarsocios(){
	int i;
    char es[50];
    int encontrado = 0;
    
    if(qtdsocios == 0){
    	printf("\t====Nenhum socio cadastrado no sistema====\n\n");
    	return;
	}
    
	printf("\t~~~~~~~~Socios~~~~~~~~\n");
	printf("\t-------------------------------------\n");
	for(i=0;i<qtdsocios;i++){
		printf("\t>%s\n",socios[i].nomeCandidato);	
		}
	printf("\t-------------------------------------\n");
	
	printf("\tDigite o nome de um dos socios acima que deseja consultar os dados:\n");
	fgets(es, sizeof(es), stdin);
    es[strcspn(es, "\n")] = '\0';
	
	
	
	for(i=0;i<Max;i++){
		if (strcasecmp(socios[i].nomeCandidato, es) == 0){
		encontrado = 1;
		printf("~\t~~~~~~Socio encontrado~~~~~~\n");
		printf("\t-----------------------------------------\n");
		printf("\tNome: %s\n",socios[i].nomeCandidato);
		printf("\tEndereco: %s\n",socios[i].localizacao.endereco);
		printf("\tCep:%s\n",socios[i].localizacao.cep);
		printf("\tBairro:%s\n",socios[i].localizacao.bairro);
		printf("\tNumero de telefone:%s\n",socios[i].contato.telefone);
		printf("\tEmail:%s\n",socios[i].contato.email);
		printf("\tNumero do cartao de socio:%ld\n",socios[i].numeroSocio);
        printf("\tCategoria: %c\n", socios[i].categoria);
		if(socios[i].qtdDependentes< 1){
		printf("\tO socio nao possui dependentes!\n");
		printf("\t-----------------------------------------\n");	
		}else {
			printf("\t-------------------------\n");
			printf("\tDependentes:\n ");
			int j;
			for(j=0;j<socios[i].qtdDependentes;j++){
				printf("\t-------------------------\n");
				printf("\tNome: %s\n",socios[i].dependente[j].nomeDependente);
				printf("\tCartao dependente: %ld\n",socios[i].dependente[j].cartaoDependente);
				printf("\tParentesco: %s\n",socios[i].dependente[j].parentesco);
				printf("\tEmail: %s\n",socios[i].dependente[j].emailDependente);
				printf("\t-------------------------\n");
			}
			}
		}
		}
		if(!encontrado){
			printf("\t====Socio não encontrado====\n");
			return;
		}
		printf("\tpressione qualquer tecla para retornar ao menu inicial\n\n");
		getchar();
	}
