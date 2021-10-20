/* origem.c (main)
 *
 * Regras básicas :
 * 1: Sempre use fgets() para strings, isso evita vários problemas de buffer.
 * 2: Não extenda a linha além de 79 colunas.
 * 3: Comente apenas o necessário, sem redundâncias.
 * 4: Use variáveis e funções com nomes auto-explicativos.
 * 5: Mantenha a indetentação e o estilo do código.
 * 6: Use snake_case e nao camelCase ou PascalCase.
 * Obrigado.
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define TAM_MAX 100

typedef struct {
	char usuario[TAM_MAX], senha[TAM_MAX];
} login_t;

typedef struct {
	int	dia, mes, ano;
} data_t;

typedef struct {
	char pais[TAM_MAX], cidade[TAM_MAX];
} naturalidade_t;

typedef struct {
	int ouro, prata, bronze;
} medalha_t;

typedef struct {
	char nome[TAM_MAX], modalidade[TAM_MAX], pais[TAM_MAX];
	char genero;
	data_t data_nascimento;
	medalha_t medalhas;
} atleta_t;

typedef struct {
	char nome[TAM_MAX], equipamentos[TAM_MAX];
	int participantes;
	bool equipe;
} modalidade_t;

typedef struct {
	char nome[TAM_MAX], descricao[TAM_MAX];
	bool destaque;
} pais_t;

typedef struct {
	char nome[TAM_MAX], tipo[TAM_MAX], endereco[TAM_MAX];
	int capacidade;
} alojamento_t;

typedef struct {
	char nome[TAM_MAX], cidade[TAM_MAX];
	int capacidade;
} local_evento_t;

typedef struct {
	char local[TAM_MAX];
	data_t data;
} treino_t;

typedef struct {
	char nome[TAM_MAX], especialidade[TAM_MAX];
	char genero;
	data_t data_nascimento;
	naturalidade_t naturalidade;
} medico_t;

// Misc
void limpa_tela();
int apenas_letras(char *texto);
void capitaliza(char *texto);
void recebe_string(char *nome, char tipo[TAM_MAX]);
char recebe_genero(char genero);
data_t recebe_data(data_t data);

// Login
void cadastra_login();
void login();

// Menus
void menu_inicial();
void menu_cadastros();
void menu_relatorios();
void menu_atletas();
void menu_logins();

// Cadastros
void cadastra_atleta();
void busca_atleta();
void lista_atletas();
void cadastra_modalidade();
void cadastra_pais();
void cadastra_medico();
void cadastra_alojamento();
void cadastra_local_evento();

// Mostradores
void mostra_atleta(atleta_t info);
void mostra_modalidade(modalidade_t info);
void mostra_pais(pais_t info);
void mostra_alojamento(alojamento_t info);
void mostra_medico(medico_t info);
void mostra_local_evento(local_evento_t info);

int main(int argc, char *argv[]) {
	printf(" ______________________________________________\n");
	printf("|                                              |\n");
	printf("|   Bem-vindo ao aplicativo de gerenciamento   |\n");
	printf("|       das Olimpiadas de Paris de 2024!       |\n");
	printf("|                                              |\n");
	printf("|                                              |\n");
	printf("|  Unip 2021 (PIM)                             |\n");
	printf("|  Por: Plinio Netto e Kelvin                  |\n");
	printf("|______________________________________________|\n");

	getchar();

	login();

	menu_inicial();

	return EXIT_SUCCESS;
}

/* Função que detecta o SO do usuário para aplicar o comando correto ao sistema.
 * É muito mais elegante do que usar apenas o comando system, já que este pode
 * variar de SO, como é o caso do cls e clear.
 */
void limpa_tela() {
	#ifdef _linux_ // se for linux.
	system("clear");
	#elif _WIN32 // se for windows.
	system("cls");
	#else

	#endif
}

/* Verifica se a string recebida contém apenas
 * letras, útil para as funções
 * de cadastro, evitanto que o usuário entre
 * com números ou caracteres especiais
 * em um campo de nome por exemplo.
 */
int apenas_letras(char *texto) {
	int i;

	for (i = 0; texto[i] != '\0'; ++i) {
		if (!isalpha(texto[i]) && texto[i] != ' ') {
			return 0; //retorna 0 indicando que não tem somente letras.
		}
	}
	return 1; //retorna 1 indicando que só tem letras.
}

/* Esta função serve para deixar uma string com as primeiras letras
 * em maiusculas. Ela utiliza comparação bit a bit para mudar a letra
 * já que a única diferença entre uma letra maiuscula e minuscula é
 * o quinto bit do ASCII.
 */
void capitaliza(char *texto) {
	for (int i = 0; i < strlen(texto); i++) {
		texto[i] |= (1 << 5);
		if (!i || texto[i - 1] == ' ')
			texto[i] &= ~(1 << 5);
	}
}

/* O ponteiro string recebe o texto, a variável tipo define se é nome,
 * modalidade, pais...
 */
void recebe_string(char *string, char tipo[TAM_MAX]) {
	do {
		printf("\n%s: ", tipo);
		fgets(string, TAM_MAX, stdin);
		string[strcspn(string, "\n")] = 0;

		if (!apenas_letras(string)) {
			printf("%s deve conter apenas letras!\n", tipo);
		}
	} while (!apenas_letras(string));

	capitaliza(string);
}

char recebe_genero(char genero) {
	do {
		printf("\nGenero (M / F): ");
		genero = getchar();
		genero = toupper(genero);

		if (genero != 'M' && genero != 'F') {
			printf("\nEntrada invalida, tente novamente.\n");
		}
	} while (genero != 'M' && genero != 'F');

	return genero;
}

data_t recebe_data(data_t data) {
	printf("\nData:\n");

	do {
		printf("Dia: ");
		scanf_s("%d%*c", &data.dia);

		if (data.dia > 32 || data.dia <= 0) {
			printf("\nDia invalido!\n");
		}
	} while (data.dia > 32 || data.dia <= 0);

	do {
		printf("Mes: ");
		scanf_s("%d%*c", &data.mes);

		if (data.mes > 13 || data.mes <= 0) {
			printf("\nMes invalido!\n");
		}
	} while (data.mes > 13 || data.mes <= 0);

	do {
		printf("Ano: ");
		scanf_s("%d%*c", &data.ano);

		if (data.ano < 1900 || data.ano > 2014) {
			printf("\nData invalida!\n");
		}
	} while (data.ano < 1900 || data.ano > 2014);

	return data;
}

/* Consegui fazer com que o programa fosse capaz de armazenar mais de
 * um login, armazenando-os em um arquivo .txt,
 */
void cadastra_login() {
	int tam_usuario, tam_senha;
	login_t login_novo;
	FILE *p_login;

	memset(&login_novo, 0, sizeof(login_t));

	do {
		printf("Cadastro de nova conta:\n");
		printf("Usuario: ");
		fgets(login_novo.usuario, TAM_MAX, stdin);

		tam_usuario = strlen(login_novo.usuario);

		if (tam_usuario < 4) {
			printf("O usuario deve conter ao menos 3 caracteres!\n\n");
		}
	} while (tam_usuario < 4);

	do {
		printf("Senha:   ");
		fgets(login_novo.senha, TAM_MAX, stdin);

		tam_senha = strlen(login_novo.senha);

		if (tam_senha < 5) {
			printf("A senha deve conter ao menos 4 caracteres!\n\n");
		}
	} while (tam_senha < 5);

	fopen_s(&p_login, "login.txt", "a"); /* Modo append */

	if (p_login == NULL) {
		printf("Erro ao abrir arquivo!\n");
		exit(EXIT_FAILURE);
	}

	fwrite(&login_novo, sizeof(login_t), 1, p_login);
	fclose(p_login); /* Não esquecer de fechar o arquivo */

	printf("Conta criada com sucesso!\n");

	getchar();
	limpa_tela();
}

/* Basicamente, usei um while para que o programa lesse todos os
 * objetos do tipo login_t no arquivo, e caso encontrasse sairia do
 * laço com um break.Acho que não é a melhor forma de fazer isso,
 * mas por enquanto foi o jeito que encontrei.
 */
void login() {
	char in_usuario[TAM_MAX], in_senha[TAM_MAX];
	bool login_correto = false;
	login_t login_info;
	FILE *p_login;

	fopen_s(&p_login, "login.txt", "r"); /* Modo Read Only */

	/* Se nenhum arquivo existir, chama a função de cadastro de login */
	if (!p_login) {
		cadastra_login();

		fopen_s(&p_login, "login.txt", "r"); /* Modo Read Only*/

		if (!p_login) {
			printf("Erro ao abrir arquivo!\n");
			exit(EXIT_FAILURE);
		}
	}

	memset(&login_info, 0, sizeof(login_t));

	while (!login_correto) {
		printf("Insira seus dados de acesso:\n");
		printf("Usuario: ");
		fgets(in_usuario, TAM_MAX, stdin);

		printf("Senha:   ");
		fgets(in_senha, TAM_MAX, stdin);

		while (!feof(p_login)) {
			fread(&login_info, sizeof(login_t), 1, p_login);

			/* Parece complexo, mas é só uma comparação entre a string
			 * inserida pelo usuário e a string salva no arquivo .txt
			 */
			if ((!strcmp(in_usuario, login_info.usuario) &&
				!strcmp(in_senha, login_info.senha))) {
				in_usuario[strcspn(in_usuario, "\n")] = 0;

				printf("\nBem vindo, %s.\n", in_usuario);

				login_correto = true;

				getchar();
				limpa_tela();

				break; /* Sai do loop while */
			}
		}

		if (!login_correto) {
			printf("\nUsuario ou senha incorreta!\n");

			rewind(p_login);

			getchar();
			limpa_tela();
		}
	}

	fclose(p_login); /* Não esquecer de fechar o arquivo */
}

/* Todos os menus seguirão este modelo de menu switch, foi o jeito mais facil
 * que encontrei, mas com certeza deve ter um jeito em que não seria
 * necessário criar um menu específico para cada tela.
 */
void menu_inicial() {
	int menu_opcao;

	do {
		printf(" ________________ MENU INICIAL ________________\n");
		printf("|                                              |\n");
		printf("|          Selecione uma das opcoes:           |\n");
		printf("|   1 - Cadastros                              |\n");
		printf("|   2 - Relatorios                             |\n");
		printf("|   3 - Gerenciamentos                         |\n");
		printf("|   4 - Alterar Logins                         |\n");
		printf("|   0 - Sair                                   |\n");
		printf("|______________________________________________|\n>>>  ");
		scanf_s("%d%*c", &menu_opcao);

		switch (menu_opcao) {
			case 1:
				limpa_tela();
				menu_cadastros();
				break;
			case 2:
				limpa_tela();
				menu_relatorios();
				break;
			case 3:
				limpa_tela();

				break;
			case 4:
				limpa_tela();
				menu_logins();
				break;
			case 0:
				printf("...Saindo...\n");
				break;
			default:
				printf("Opcao invalida, tente novamente!\n");
				getchar();
				limpa_tela();
				break;
		}
	} while (menu_opcao != 0);
}

void menu_cadastros() {
	int menu_opcao;

	do {
		printf(" _______________ MENU CADASTROS _______________\n");
		printf("|                                              |\n");
		printf("|         Selecione uma das opcoes:            |\n");
		printf("|   1 - Atletas                                |\n");
		printf("|   2 - Modalidades Olimpicas                  |\n");
		printf("|   3 - Paises Participantes                   |\n");
		printf("|   4 - Alojamentos                            |\n");
		printf("|   5 - Locais de Eventos                      |\n");
		printf("|   6 - Agendamento de Treino                  |\n");
		printf("|   7 - Medicos                                |\n");
		printf("|   8 - Funcionarios                           |\n");
		printf("|   9 - Voluntarios                            |\n");
		printf("|  10 - Controle de Contingente (COVID-19)     |\n");
		printf("|   0 - Voltar                                 |\n");
		printf("|______________________________________________|\n>>>  ");
		scanf_s("%d%*c", &menu_opcao);

		switch (menu_opcao) {
			case 1:
				limpa_tela();
				cadastra_atleta();
				break;
			case 2:
				limpa_tela();
				cadastra_modalidade();
				break;
			case 3:
				limpa_tela();
				cadastra_pais();
				break;
			case 4:
				limpa_tela();
				cadastra_alojamento();
				break;
			case 5:
				limpa_tela();
				cadastra_local_evento();
				break;
			case 6:
				limpa_tela();
				break;
			case 7:
				limpa_tela();
				break;
			case 8:
				limpa_tela();
				break;
			case 9:
				limpa_tela();
				break;
			case 10:
				limpa_tela();
				break;
			case 11:
				limpa_tela();
				break;
			case 0:
				limpa_tela();
				break;
			default:
				printf("\nOpcao invalida, tente novamente!\n");
				getchar();
				limpa_tela();
				break;
		}
	} while (menu_opcao != 0);
}

void menu_relatorios() {
	int menu_opcao;

	do {
		printf(" _______________ MENU RELATORIOS ______________\n");
		printf("|                                              |\n");
		printf("|         Selecione uma das opcoes:            |\n");
		printf("|   1 - Calendario Olimpico                    |\n");
		printf("|   2 - Contagem de Medalhas                   |\n");
		printf("|   3 - Medalhistas                            |\n");
		printf("|   4 - Total de Medalhas Distribuidas         |\n");
		printf("|   0 - Voltar                                 |\n");
		printf("|______________________________________________|\n>>>  ");
		scanf_s("%d%*c", &menu_opcao);

		switch (menu_opcao) {
			case 1:
				limpa_tela();
				menu_atletas();
				break;
			case 2:
				printf("Opcao 2");
				break;
			case 3:
				printf("Opcao 3");
				break;
			case 4:
				printf("Opcao 4");
				break;
			case 5:
				printf("Opcao 5");
				break;
			case 6:
				printf("Opcao 6");
				break;
			case 0:
				limpa_tela();
				break;
			default:
				printf("\nOpcao invalida, tente novamente!\n");
				getchar();
				limpa_tela();
				break;
		}
	} while (menu_opcao != 0);
}

/* Talvez vá para a área de gerenciamento */
void menu_atletas() {
	int opcao_menu;

	do {
		printf(" ___________________ Atletas __________________\n");
		printf("|                                              |\n");
		printf("|         Selecione uma das opcoes:            |\n");
		printf("|   1 - Procurar                               |\n");
		printf("|   2 - Listar                                 |\n");
		printf("|   0 - Voltar                                 |\n");
		printf("|______________________________________________|\n>>>  ");
		scanf_s("%d%*c", &opcao_menu);

		switch (opcao_menu) {
			case 1:
				limpa_tela();
				busca_atleta();
				break;
			case 2:
				limpa_tela();
				lista_atletas();
				break;
			case 0:
				limpa_tela();
				break;
			default:
				printf("\nOpcao invalida, tente novamente!\n");
				getchar();
				limpa_tela();
				break;
		}
	} while (opcao_menu != 0);
}

void menu_logins() {
	int opcao_menu;

	do {
		printf(" ___________________ LOGINS ___________________\n");
		printf("|                                              |\n");
		printf("|         Selecione uma das opcoes:            |\n");
		printf("|   1 - Novo Login                             |\n");
		printf("|   2 - Logins Cadastrados                     |\n");
		printf("|   3 - Remover Login                          |\n");
		printf("|   0 - Voltar                                 |\n");
		printf("|______________________________________________|\n>>>  ");
		scanf_s("%d%*c", &opcao_menu);

		switch (opcao_menu) {
			case 1:
				limpa_tela();
				cadastra_login();

				break;
			case 2:
				limpa_tela();
				lista_atletas();

				break;
			case 3:
				printf("Opcao 3");
				break;
			case 0:
				limpa_tela();
				break;
			default:
				printf("\nOpcao invalida, tente novamente!\n");

				getchar();
				limpa_tela();

				break;
		}
	} while (opcao_menu != 0);
}

/* Funciona basicamente como o cadastro de login. Recebe as informações
 * em um objeto do tipo em questão e o armazena em arquivo .txt . Um
 * aqruivo binário talves fosse melhor para este caso, mas o pdf do
 * PIM especifica que os dados devem ser salvos em .txt .
 */
void cadastra_atleta() {
	int manter;
	atleta_t novo_atleta, info_atleta;
	FILE *p_atletas;

	memset(&novo_atleta, 0, sizeof(atleta_t));
	memset(&info_atleta, 0, sizeof(atleta_t));

	

	printf("Insira as informacoes do atleta:\n");

	recebe_string(novo_atleta.nome, "Nome");

	fopen_s(&p_atletas, "atletas.txt", "r");

	if(p_atletas != NULL) {

		while (!feof(p_atletas)) {
			fread(&info_atleta, sizeof(atleta_t), 1, p_atletas);

			if (!strcmp(info_atleta.nome, novo_atleta.nome)) {
				printf("\n");
				mostra_atleta(info_atleta);

				printf("Este atleta já existe!\n");

				rewind(p_atletas);

				getchar();
				limpa_tela();

				return;
			}
		}

		fclose(p_atletas);
	}

	novo_atleta.genero = recebe_genero(novo_atleta.genero);

	novo_atleta.data_nascimento = recebe_data(novo_atleta.data_nascimento);

	recebe_string(novo_atleta.pais, "Pais");

	recebe_string(novo_atleta.modalidade, "Modalidade");

	limpa_tela();
	mostra_atleta(novo_atleta);

	printf("\nOs dados estao corretos?\n1 = Sim / 0 = Nao\n>>>   ");
	scanf_s("%d%*c", &manter);

	do {
		switch (manter) {
		case 0:
			printf("Descartando informacoes...\n");
			break;
		case 1:
			fopen_s(&p_atletas, "atletas.txt", "a");
			if (p_atletas == NULL) {
				printf("Erro ao abrir arquivo!\n");
				exit(EXIT_FAILURE);
			}
			fwrite(&novo_atleta, sizeof(atleta_t), 1, p_atletas);
			fclose(p_atletas);
			printf("Cadastro concluido com sucesso!\n");
			break;
		default:
			printf("\nOpcao invalida, tente novamente!\n");
			break;
		}
	} while (manter != 0 && manter != 1);

	getchar();
	limpa_tela();
}

void busca_atleta() {
	int i = 0;
	char nome_atleta[TAM_MAX];
	bool encontrado = false;
	atleta_t atleta_info;
	FILE *p_atletas;

	// Abre o arquivo em modo read only.
	fopen_s(&p_atletas, "atletas.txt", "r");

	// Se não houver arquivo ou se o arquivo estiver vazio.
	if (!p_atletas) {
		printf("Nenhum cadastro foi encontrado!\n");

		getchar();
		limpa_tela();

		return;
	}

	memset(&atleta_info, 0, sizeof(atleta_t));

	printf("\nInsira o nome do atleta desejado: ");
	fgets(&nome_atleta, TAM_MAX, stdin);

	// Remove o enter da string (problmea de buffer).
	nome_atleta[strcspn(nome_atleta, "\n")] = 0;

	// Enquanto não chegar ao final do arquivo (eof = end of file), faça:
	while (!feof(p_atletas)) {
		fread(&atleta_info, sizeof(atleta_t), 1, p_atletas);

		// Compara as strings
		if (!(strcmp(atleta_info.nome, nome_atleta))) {
			printf("\n");
			mostra_atleta(atleta_info);

			encontrado = true;

			printf("1 - Alterar");
			printf("2 - Excluir");
			printf("3 - Voltar");

			rewind(p_atletas);

			getchar();
			limpa_tela();

			break;
		}

		i++;
	}

	// Se nada for encontrado:
	if (!encontrado) {
		printf("\nAtleta nao foi encontrado!\n");

		getchar();
		limpa_tela();
	}

	fclose(p_atletas); // fecha o arquivo.
}

void lista_atletas() {
	atleta_t atleta_info;
	FILE *p_atletas;

	// Abre o arquivo binário em modo read only.
	fopen_s(&p_atletas, "atletas.txt", "r");

	// Se não houver arquivo ou se o arquivo estiver vazio.
	if (!p_atletas) {
		printf("Nenhum cadastro foi encontrado!\n");

		fclose(p_atletas);

		getchar();
		limpa_tela();

		return;
	}

	memset(&atleta_info, 0, sizeof(atleta_t));

	// Enquanto não chegar ao final do arquivo (eof = end of file), faça:
	do {
		fread(&atleta_info, sizeof(atleta_t), 1, p_atletas);
		if (feof(p_atletas)) {
			break;
		}
		mostra_atleta(atleta_info);
	} while (!feof(p_atletas));

	fclose(p_atletas);

	getchar();
	limpa_tela();
}

void cadastra_modalidade() {
	int manter, opcao;
	modalidade_t nova_modalidade;
	FILE *p_modalidades;

	memset(&nova_modalidade, 0, sizeof(modalidade_t));

	printf("Insira as informacoes da modalidade:\n");
	printf("\nNome: ");
	fgets(nova_modalidade.nome, TAM_MAX, stdin);
	nova_modalidade.nome[strcspn(nova_modalidade.nome, "\n")] = 0;
	capitaliza(&nova_modalidade.nome);

	printf("\nEquipamentos necessarios: ");
	fgets(nova_modalidade.equipamentos, TAM_MAX, stdin);
	nova_modalidade.equipamentos
		[strcspn(nova_modalidade.equipamentos, "\n")] = 0;
	nova_modalidade.equipamentos[0] =
		toupper(nova_modalidade.equipamentos[0]);

	do {
		printf("\nNumero participantes por evento/partida: ");
		scanf_s("%d%*c", &nova_modalidade.participantes);
		if (nova_modalidade.participantes <= 0) {
			printf("\nEntrada invalida, tente novamente!\n");
		}
	} while (nova_modalidade.participantes <= 0);

	do {
		printf("\nEm equipe?\n1 = Sim / 0 = Nao\n>>>   ");
		scanf_s("%d%*c", &opcao);

		switch (opcao) {
			case 0:
				nova_modalidade.equipe = false;
				break;
			case 1:
				nova_modalidade.equipe = true;
				break;
			default:
				printf("\nOpcao invalida, tente novamente!\n");
				break;
		}
	} while (opcao != 0 && opcao != 1);

	limpa_tela();
	mostra_modalidade(nova_modalidade);

	printf("\nOs dados estao corretos?\n1 = Sim / 0 = Nao\n>>>   ");
	scanf_s("%d%*c", &manter);

	do {
		switch (manter) {
			case 0:
				printf("Descartando informacoes...\n");
				break;
			case 1:
				fopen_s(&p_modalidades, "modalidades.txt", "a");
				if (p_modalidades == NULL) {
					printf("Erro ao abrir arquivo!\n");
					exit(EXIT_FAILURE);
				}
				fwrite(&nova_modalidade, sizeof(modalidade_t), 1, p_modalidades);
				fclose(p_modalidades);
				printf("Cadastro concluido com sucesso!\n");
				break;
			default:
				printf("\nOpcao invalida, tente novamente!\n");
				break;
		}
	} while (manter != 0 && manter != 1);

	getchar();
	limpa_tela();
}

void cadastra_pais() {
	int manter, opcao;
	pais_t novo_pais;
	FILE *p_paises;

	memset(&novo_pais, 0, sizeof(pais_t));

	printf("Insira as informacoes do pais:\n");
	do {
		printf("\nNome do pais: ");
		fgets(novo_pais.nome, TAM_MAX, stdin);
		novo_pais.nome[strcspn(novo_pais.nome, "\n")] = 0;

		if (!(apenas_letras(novo_pais.nome))) {
			printf("O nome do pais deve conter apenas letras!\n");
		}
	} while (!(apenas_letras(novo_pais.nome)));

	capitaliza(&novo_pais.nome);

	printf("\nDescricao rapida: ");
	fgets(novo_pais.descricao, TAM_MAX, stdin);
	novo_pais.descricao[strcspn(novo_pais.descricao, "\n")] = 0;
	novo_pais.descricao[0] = toupper(novo_pais.descricao[0]);

	do {
		printf("\nO pais e destaque?\n1 = Sim / 0 = Nao\n>>>   ");
		scanf_s("%d%*c", &opcao);

		switch (opcao) {
			case 0:
				novo_pais.destaque = false;
				break;
			case 1:
				novo_pais.destaque = true;
				break;
			default:
				printf("\nOpcao invalida, tente novamente!\n");
				break;
		}
	} while (opcao != 0 && opcao != 1);

	limpa_tela();
	mostra_pais(novo_pais);

	printf("\nOs dados estao corretos?\n1 = Sim / 0 = Nao\n>>>   ");
	scanf_s("%d%*c", &manter);

	do {
		switch (manter) {
			case 0:
				printf("Descartando informacoes...\n");
				break;
			case 1:
				fopen_s(&p_paises, "modalidades.txt", "a");
				if (p_paises == NULL) {
					printf("Erro ao abrir arquivo!\n");
					exit(EXIT_FAILURE);
				}
				fwrite(&p_paises, sizeof(pais_t), 1, p_paises);
				fclose(p_paises);
				printf("Cadastro concluido com sucesso!\n");
				break;
			default:
				printf("\nOpcao invalida, tente novamente!\n");
				break;
		}
	} while (manter != 0 && manter != 1);

	getchar();
	limpa_tela();
}

void cadastra_alojamento() {
	int manter;
	alojamento_t novo_alojamento;
	FILE *p_alojamento;

	memset(&novo_alojamento, 0, sizeof(alojamento_t));

	printf("Insira as informacoes do alojamento:\n");

	printf("\nNome do alojamento: ");
	fgets(novo_alojamento.nome, TAM_MAX, stdin);
	novo_alojamento.nome[strcspn(novo_alojamento.nome, "\n")] = 0;
	capitaliza(&novo_alojamento.nome);

	printf("\nTipo do alojamento: ");
	fgets(novo_alojamento.tipo, TAM_MAX, stdin);
	novo_alojamento.tipo[strcspn(novo_alojamento.tipo, "\n")] = 0;
	novo_alojamento.tipo[0] = toupper(novo_alojamento.tipo[0]);

	printf("\nEndereco: ");
	fgets(novo_alojamento.endereco, TAM_MAX, stdin);
	novo_alojamento.endereco[strcspn(novo_alojamento.endereco, "\n")] = 0;
	capitaliza(&novo_alojamento.endereco);

	do {
		printf("Capacidade: ");
		scanf_s("%d%*c", &novo_alojamento.capacidade);

		if (novo_alojamento.capacidade <= 0) {
			printf("Entrada inválida, tente novamente!\n");
		}
	} while (novo_alojamento.capacidade <= 0);

	limpa_tela();
	mostra_alojamento(novo_alojamento);

	printf("\nOs dados estao corretos?\n1 = Sim / 0 = Nao\n>>>   ");
	scanf_s("%d%*c", &manter);

	do {
		switch (manter) {
			case 0:
				printf("Descartando informacoes...\n");
				break;
			case 1:
				fopen_s(&p_alojamento, "alojamentos.txt", "a");
				if (p_alojamento == NULL) {
					printf("Erro ao abrir arquivo!\n");
					exit(EXIT_FAILURE);
				}
				fwrite(&p_alojamento, sizeof(alojamento_t), 1, p_alojamento);
				fclose(p_alojamento);
				printf("Cadastro concluido com sucesso!\n");
				break;
			default:
				printf("\nOpcao invalida, tente novamente!\n");
				break;
		}
	} while (manter != 0 && manter != 1);

	getchar();
	limpa_tela();
}

void cadastra_local_evento() {
	int manter;
	local_evento_t novo_local_evento;
	FILE* p_local_evento;

	memset(&novo_local_evento, 0, sizeof(local_evento_t));

	printf("Insira as informacoes do local de evento:\n");

	printf("\nNome do local: ");
	fgets(novo_local_evento.nome, TAM_MAX, stdin);
	novo_local_evento.nome[strcspn(novo_local_evento.nome, "\n")] = 0;
	capitaliza(&novo_local_evento.nome);

	printf("\nLocalizacao do local: ");
	fgets(novo_local_evento.cidade, TAM_MAX, stdin);
	novo_local_evento.cidade[strcspn(novo_local_evento.cidade, "\n")] = 0;
	novo_local_evento.cidade[0] = toupper(novo_local_evento.cidade[0]);

	do {
		printf("Capacidade: ");
		scanf_s("%d%*c", &novo_local_evento.capacidade);

		if (novo_local_evento.capacidade <= 0) {
			printf("Entrada inválida, tente novamente!\n");
		}
	} while (novo_local_evento.capacidade <= 0);

	limpa_tela();
	mostra_local_evento(novo_local_evento);

	printf("\nOs dados estao corretos?\n1 = Sim / 0 = Nao\n>>>   ");
	scanf_s("%d%*c", &manter);

	do {
		switch (manter) {
		case 0:
			printf("Descartando informacoes...\n");
			break;
		case 1:
			fopen_s(&p_local_evento, "local_evento.txt", "a");
			if (p_local_evento == NULL) {
				printf("Erro ao abrir arquivo!\n");
				exit(EXIT_FAILURE);
			}
			fwrite(&p_local_evento, sizeof(local_evento_t), 1,
				p_local_evento);
			fclose(p_local_evento);
			printf("Cadastro concluido com sucesso!\n");
			break;
		default:
			printf("\nOpcao invalida, tente novamente!\n");
			break;
		}
	} while (manter != 0 && manter != 1);

	getchar();
	limpa_tela();
}

/*
void agenda_treino() {
	int manter;
	treino_t novo_treino;
	FILE* p_treinos;

	printf("Insira as informacoes do treino:\n");

	printf("\n\nLocal: ");
	fgets(novo_treino.local, TAM_MAX, stdin);
	novo_treino.local[strcspn(novo_treino.local, "\n")] = 0;
	capitaliza(&novo_treino.local);

	printf("\nData:\n");
	printf("Dia: ");
	scanf_s("%d%*c", &novo_treino.data.dia);

	limpa_tela();
	mostra_local_evento(novo_local_evento);

	printf("\nOs dados estao corretos?\n1 = Sim / 0 = Nao\n>>>   ");
	scanf_s("%d%*c", &manter);

	do {
		switch (manter) {
		case 0:
			printf("Descartando informacoes...\n");
			break;
		case 1:
			fopen_s(&p_local_evento, "local_evento.txt", "a");
			if (p_local_evento == NULL) {
				printf("Erro ao abrir arquivo!\n");
				exit(EXIT_FAILURE);
			}
			fwrite(&p_local_evento, sizeof(local_evento_t), 1,
				p_local_evento);
			fclose(p_local_evento);
			printf("Cadastro concluido com sucesso!\n");
			break;
		default:
			printf("\nOpcao invalida, tente novamente!\n");
			break;
		}
	} while (manter != 0 && manter != 1);

	getchar();
	limpa_tela();
}
*/

void cadastra_medico() {
	int opcao;
	medico_t novo_medico;
	FILE *p_medicos;

	memset(&novo_medico, 0, sizeof(medico_t));

	printf("Insira as informacoes do atleta:\n");

	do {
		printf("\nNome completo: ");
		fgets(novo_medico.nome, TAM_MAX, stdin);

		// Remove o enter da string (problema de buffer).
		novo_medico.nome[strcspn(novo_medico.nome, "\n")] = 0;

		if (!(apenas_letras(novo_medico.nome))) {
			printf("O nome deve conter apenas letras!\n");
		}
	} while (!(apenas_letras(novo_medico.nome)));

	do {
		printf("\nGenero (M / F): ");
		novo_medico.genero = getchar();
		novo_medico.genero = toupper(novo_medico.genero);

		if (novo_medico.genero != 'M' && novo_medico.genero != 'F') {
			printf("\nEntrada invalida, tente novamente.\n");
		}
	} while (novo_medico.genero != 'M' && novo_medico.genero != 'F');

	printf("\nData de nascimento:\n");

	do {
		printf("Dia: ");
		scanf_s("%d%*c", &novo_medico.data_nascimento.dia);

		if (novo_medico.data_nascimento.dia > 32 ||
			novo_medico.data_nascimento.dia <= 0) {
			printf("\nData invalida!\n");
		}
	} while (novo_medico.data_nascimento.dia > 32 ||
			 novo_medico.data_nascimento.dia <= 0);

	do {
		printf("Mes: ");
		scanf_s("%d%*c", &novo_medico.data_nascimento.mes);

		if (novo_medico.data_nascimento.mes > 13 ||
			novo_medico.data_nascimento.mes <= 0) {
			printf("\nData invalida!\n");
		}
	} while (novo_medico.data_nascimento.mes > 13 ||
			 novo_medico.data_nascimento.mes <= 0);

	do {
		printf("Ano: ");
		scanf_s("%d%*c", &novo_medico.data_nascimento.ano);

		if (novo_medico.data_nascimento.ano < 1960 ||
			novo_medico.data_nascimento.ano > 2014) {
			printf("\nData invalida!\n");
		}
	} while (novo_medico.data_nascimento.ano < 1960 ||
			 novo_medico.data_nascimento.ano > 2014);

	printf("\nNaturalidade:\n");

	do {
		printf("Pais: ");
		fgets(novo_medico.naturalidade.pais, TAM_MAX, stdin);

		// Remove o enter da string (problema de buffer).
		novo_medico.naturalidade.pais[strcspn(novo_medico.naturalidade.pais,
											  "\n")] = 0;

		 // Se não for somente letras.
		if (!(apenas_letras(novo_medico.naturalidade.pais))) {
			printf("O nome do pais deve conter apenas letras!\n");
		}
	} while (!(apenas_letras(novo_medico.naturalidade.pais)));

	do {
		printf("Cidade: ");
		fgets(novo_medico.naturalidade.cidade, TAM_MAX, stdin);

		// Remove o enter da string (problema de buffer).
		novo_medico.naturalidade.cidade[strcspn
		(novo_medico.naturalidade.cidade, "\n")] = 0;

		// Se não for somente letras:
		if (!(apenas_letras(novo_medico.naturalidade.cidade))) {
			printf("O nome da cidade deve conter apenas letras!\n");
		}
	} while (!(apenas_letras(novo_medico.naturalidade.cidade)));

	do {
		printf("\nEspecialidade médica: ");
		fgets(novo_medico.especialidade, TAM_MAX, stdin);

		// Remove o enter da string (problema de buffer).
		novo_medico.especialidade[strcspn(novo_medico.especialidade, "\n")] = 0;

		// Se não for somente letras:
		if (!(apenas_letras(novo_medico.especialidade))) {
			printf("A especialidade deve conter apenas letras!\n");
		}
	} while (!(apenas_letras(novo_medico.especialidade)));

	limpa_tela();
	mostra_medico(novo_medico);

	printf("\nOs dados estao corretos?\n1 = Sim / 0 = Nao\n>>>   ");
	scanf_s("%d%*c", &opcao);

	if (opcao == 1) {
		// Abre o arquivo no modo append.
		fopen_s(&p_medicos, "medicos.txt", "a");

		// Tratamento de erro:
		if (p_medicos == NULL) {
			printf("Erro ao abrir arquivo!\n");
			exit(1);
		}

		// Adiciona no arquivo.
		fwrite(&novo_medico, sizeof(atleta_t), 1, p_medicos);
		fclose(p_medicos);

		printf("Cadastro concluido com sucesso!\n");
	}

	else {
		printf("Descartando informacoes...\n");
	}

	getchar();
	limpa_tela();
}

void mostra_atleta(atleta_t info) {
	printf("Informacoes do Atleta:\n\nNome: %s\n", info.nome);
	printf("Genero: %c\n", info.genero);
	printf("Data de Nascimento: %02d/%02d/%d\n", info.data_nascimento.dia,
		   info.data_nascimento.mes, info.data_nascimento.ano);
	printf("Naturalidade: %s\n", info.pais);
	printf("Modalidade Esportiva: %s\n\n\n", info.modalidade);
}

void mostra_modalidade(modalidade_t info) {
	printf("Informacoes da Modalidade:\n\nNome: %s\n", info.nome);
	printf("Equipamentos Necessarios: %s\n", info.equipamentos);
	if (info.equipe) {
		printf("Esporte Coletivo\n\n\n");
	} else {
		printf("Esporte Individual\n\n\n");
	}
}

void mostra_pais(pais_t info) {
	printf("Informacoes do Pais:\n\nNome: %s\n", info.nome);
	printf("Descricao: %s\n", info.descricao);
	if (info.destaque) {
		printf("Destaque!\n\n\n");
	}
}

void mostra_alojamento(alojamento_t info) {
	printf("Informacoes do Alojamento:\n\nNome: %s\n", info.nome);
	printf("Tipo do Alojamento: %s\n", info.tipo);
	printf("Endereco: %s\n", info.endereco);
	printf("Capacidade: %d pessoas\n", info.capacidade);
}

void mostra_local_evento(local_evento_t info) {
	printf("Informacoes do Local de Evento:\n\nNome: %s\n", info.nome);
	printf("Local do Evento: %s\n", info.cidade);
	printf("Capacidade: %d pessoas\n", info.capacidade);
}

void mostra_medico(medico_t info) {
	printf("Informacoes do Atleta:\n\nNome: %s\n", info.nome);
	printf("Genero: %c\n", info.genero);
	printf("Data de Nascimento: %02d/%02d/%d\n", info.data_nascimento.dia,
		   info.data_nascimento.mes,
		   info.data_nascimento.ano);
	printf("Naturalidade: %s, %s\n", info.naturalidade.cidade,
		   info.naturalidade.pais);
	printf("Especialidade Médica: %s\n\n\n", info.especialidade);
}

// Executar programa: ctrl + f5 ou menu depurar > iniciar sem depuração
// Depurar programa: f5 ou menu depurar > iniciar depuração