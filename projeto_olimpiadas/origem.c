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

/* STRUCTS */

typedef struct {
	char usuario[TAM_MAX], senha[TAM_MAX];
} login_t;

typedef struct {
	int	dia, mes, ano;
} data_t;

typedef struct {
	char pais[TAM_MAX], cidade[TAM_MAX];
} local_t;

typedef struct {
	int ouro, prata, bronze;
} medalha_t;

typedef struct {
	int capacidade;
	char nome[TAM_MAX], cidade[TAM_MAX], modalidade[TAM_MAX], 
		equipamentos[TAM_MAX], participantes[TAM_MAX];
	data_t data;
} evento_t;

typedef struct {
	int id;
	float altura, peso;
	char nome[TAM_MAX], modalidade[TAM_MAX], alojamento[TAM_MAX];
	char genero;
	bool vacina;
	local_t naturalidade;
	data_t data;
	medalha_t medalhas;
} atleta_t;

typedef struct {
	int id;
	char nome[TAM_MAX], modalidade[TAM_MAX], pais[TAM_MAX];
	medalha_t medalhas;
} equipe_t;

typedef struct {
	char local[TAM_MAX];
	data_t data;
} treino_t;

typedef struct {
	int id;
	char nome[TAM_MAX], especialidade[TAM_MAX], pais[TAM_MAX], 
		funcao[TAM_MAX], alojamento[TAM_MAX];
	char genero;
	bool voluntario;
	data_t data;
} funcionario_t;

/* FUNÇÕES */

/* MISC */

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
int apenas_letras(char* texto) {
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
void capitaliza(char* texto) {
	for (int i = 0; i < strlen(texto); i++) {
		texto[i] |= (1 << 5);
		if (!i || texto[i - 1] == ' ')
			texto[i] &= ~(1 << 5);
	}
}

int compara_datas(data_t data1, data_t data2) {
	if (data1.dia == data2.dia && data1.mes == data2.mes &&
		data1.ano == data2.ano) {
		return 0;
	}
	else {
		return 1;
	}
}

/* RECEPTORAS */

/* O ponteiro string recebe o texto, a variável tipo define se é nome,
 * modalidade, pais...
 */
void recebe_string(char* string, char tipo[TAM_MAX]) {
	printf("\n%s: ", tipo);
	fgets(string, TAM_MAX, stdin);
	string[strcspn(string, "\n")] = 0;
	string[0] = toupper(string[0]);
}

/* Fiz esta função especificamente para receber nomes, ou seja, qualquer
 * string que passe por essa função vai ser capitalizada e filtrada para
 * que contenha apenas letras.
 */
void recebe_nome(char* nome, char tipo[TAM_MAX]) {
	do {
		printf("\nNome %s: ", tipo);
		fgets(nome, TAM_MAX, stdin);
		nome[strcspn(nome, "\n")] = 0;
		capitaliza(nome);

		if (!apenas_letras(nome)) {
			printf("O nome deve conter apenas letras!\n");
		}
	} while (!apenas_letras(nome));
}

/* Recebe uma variável do tipo char, compara e passa para maiúsculo.*/
char recebe_genero() {
	char genero;

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

/* Função para receber datas, com as condicionais para receber apenas
 * números compativeis com datas.
 */
data_t recebe_data() {
	data_t data;

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

		if (data.ano < 1900 || data.ano > 2025) {
			printf("\nData invalida!\n");
		}
	} while (data.ano < 1900 || data.ano > 2025);

	return data;
}

local_t recebe_local() {
	local_t nat;

	do {
		printf("Cidade: ");
		fgets(nat.cidade, TAM_MAX, stdin);
		nat.cidade[strcspn(nat.cidade, "\n")] = 0;
		capitaliza(&nat.cidade);

		if (!apenas_letras(nat.cidade)) {
			printf("O nome da cidade conter apenas letras!\n");
		}
	} while (!apenas_letras(nat.cidade));

	do {
		printf("\nPais: ");
		fgets(nat.pais, TAM_MAX, stdin);
		nat.pais[strcspn(nat.pais, "\n")] = 0;
		capitaliza(&nat.pais);

		if (!apenas_letras(nat.pais)) {
			printf("O nome do pais deve conter apenas letras!\n");
		}
	} while (!apenas_letras(nat.pais));

	return nat;
}

int recebe_inteiro(char tipo[TAM_MAX]) {
	int numero;

	do {
		printf("\n%s: ", tipo);
		scanf_s("%d%*c", &numero);
		if (numero <= 0) {
			printf("\nEntrada invalida, tente novamente!\n");
		}
	} while (numero <= 0);

	return numero;
}

float recebe_flutuante(char tipo[TAM_MAX]) {
	float numero;
	do {
		printf("\n%s: ", tipo);
		scanf_s("%f%*c", &numero);
		if (numero <= 0) {
			printf("\nEntrada invalida, tente novamente!\n");
		}
	} while (numero <= 0);

	return numero;
}

bool recebe_bool(char tipo[TAM_MAX]) {
	bool booleano;
	int opcao;

	do {
		printf("\n%s?\n1 = Sim / 0 = Nao\n>>>   ", tipo);
		scanf_s("%d%*c", &opcao);

		switch (opcao) {
		case 0:
			booleano = false;
			break;
		case 1:
			booleano = true;
			break;
		default:
			printf("\nOpcao invalida, tente novamente!\n");
			break;
		}
	} while (opcao != 0 && opcao != 1);

	return booleano;
}

int recebe_id() {
	int id;

	do {
		printf("\nID: ");
		scanf_s("%d%*c", &id);
		if (id <= 0 || id > 9999) {
			printf("\nEntrada invalida, tente novamente!\n");
		}
	} while (id <= 0);

	return id;
}

/* LOGIN */

void cadastra_login() {
	int tam_usuario, tam_senha;
	login_t login_novo;
	FILE* p_login;

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

void login() {
	char in_usuario[TAM_MAX], in_senha[TAM_MAX];
	bool login_correto = false;
	login_t login_info;
	FILE* p_login;

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

/* Mostradores */

void mostra_funcionario(funcionario_t info) {
	printf("Informacoes do Funcionario:\n\nID: %d\n", info.id);
	printf("Nome: %s\n", info.nome);
	printf("Genero: %c\n", info.genero);
	printf("Data de Nascimento: %02d/%02d/%d\n", info.data.dia,
		info.data.mes, info.data.ano);
	printf("Naturalidade: %s\n", info.pais);
	printf("Alojamento: %s\n", info.alojamento);
	printf("Função: %s\n", info.funcao);
	printf("Especialidade: %s\n", info.especialidade);
	if (!info.voluntario) {
		printf("Voluntario: Nao\n\n\n");
	}
	else {
		printf("Voluntario: Sim\n\n\n");
	}
}

void mostra_treino(treino_t info) {
	printf("Informacoes do Treino:\n\Local: %s\n", info.local);
	printf("Data: %02d/%02d/%d\n", info.data.dia, info.data.mes,
		info.data.ano);
}

void mostra_evento(evento_t info) {
	printf("Informacoes do Evento:\n\nArena: %s\n", info.nome);
	printf("Local: %s\n", info.cidade);
	printf("Data: %02d/%02d/%d\n", info.data.dia, info.data.mes,
		info.data.ano);
	printf("Modalidade Esportiva: %s\n", info.modalidade);
	printf("Participantes: %s\n", info.participantes);
	printf("Equipamentos Necessarios: %s\n", info.equipamentos);
	printf("Capacidade: %d pessoas\n", info.capacidade);
}

void mostra_atleta(atleta_t info) {
	printf("Informacoes do Atleta:\n\nID: %04d\n", info.id);
	printf("Nome: %s\n", info.nome);
	printf("Genero: %c\n", info.genero);
	printf("Data de Nascimento: %02d/%02d/%d\n", info.data.dia,
		info.data.mes, info.data.ano);
	printf("Naturalidade: %s, %s\n", 
		info.naturalidade.cidade, info.naturalidade.pais);
	printf("Modalidade Esportiva: %s\n", info.modalidade);
	printf("Alojamento: %s\n", info.alojamento);
	printf("Altura: %.2f m\n", info.altura);
	printf("Peso: %.2f kg\n", info.peso);
	printf("Vacinado contra o COVID-19: ");
	if (info.vacina) {
		printf("Sim\n\n\n");
	}
	else {
		printf("Nao\n\n\n");
	}
}

void mostra_equipe(equipe_t info) {
	printf("Informacoes da Equipe:\n\nID: %d\n", info.id);
	printf("Nome: %s\n", info.nome);
	printf("Pais: %s\n", info.pais);
	printf("Modalidade: %s\n", info.modalidade);
}

/* CADASTROS */

void lista_funcionarios() {
	funcionario_t info_funcionario;
	FILE *p_funcionarios;

	fopen_s(&p_funcionarios, "funcionarios.txt", "r");

	if (!p_funcionarios) {
		printf("Nenhum cadastro foi encontrado!\n");

		getchar();
		limpa_tela();

		return;
	}

	memset(&info_funcionario, 0, sizeof(funcionario_t));

	do {
		fread(&info_funcionario, sizeof(funcionario_t), 1, p_funcionarios);
		if (feof(p_funcionarios)) {
			break;
		}
		mostra_funcionario(info_funcionario);
	} while (!feof(p_funcionarios));

	fclose(p_funcionarios);

	getchar();
	limpa_tela();
}

void busca_funcionario() {
	int manter, id;
	bool encontrado = false;
	funcionario_t info_funcionario;
	FILE *p_funcionario;

	fopen_s(&p_funcionario, "funcionarios.txt", "r");

	if (!p_funcionario) {
		printf("Nenhum cadastro foi encontrado!\n");

		getchar();
		limpa_tela();

		return;
	}

	memset(&info_funcionario, 0, sizeof(funcionario_t));

	printf("\nInsira o ID do funcionario desejado: ");
	id = recebe_id();

	while (!feof(p_funcionario)) {
		fread(&info_funcionario, sizeof(funcionario_t), 1, p_funcionario);

		if (id == info_funcionario.id) {
			printf("\n");
			mostra_funcionario(info_funcionario);

			encontrado = true;

			printf("\nDeseja excluir?\n1 = Sim / 0 = Nao\n>>>   ");
			scanf_s("%d%*c", &manter);

			do {
				switch (manter) {
					case 0:
						break;
					case 1:
						fopen_s(&p_funcionario, "funcionarios.txt", "a");
						if (p_funcionario == NULL) {
							printf("Erro ao abrir arquivo!\n");
							exit(EXIT_FAILURE);
						}
						memset(&info_funcionario, ' ', sizeof(funcionario_t));
						fwrite(&info_funcionario, sizeof(funcionario_t), 1, p_funcionario);
						fclose(p_funcionario);
						printf("Item Removido!\n");
						break;
					default:
						printf("\nOpcao invalida, tente novamente!\n");
						break;
				}
			} while (manter != 0 && manter != 1);

			rewind(p_funcionario);

			getchar();
			limpa_tela();

			break;
		}
	}

	if (!encontrado) {
		printf("\nAtleta nao foi encontrado!\n");

		getchar();
		limpa_tela();
	}

	fclose(p_funcionario);
}

void cadastra_funcionario() {
	int manter;
	funcionario_t novo_funcionario, info_funcionario;
	FILE* p_funcionario;

	memset(&novo_funcionario, 0, sizeof(funcionario_t));
	memset(&info_funcionario, 0, sizeof(funcionario_t));

	printf("Insira as informacoes do atleta:\n");

	novo_funcionario.id = recebe_inteiro("ID do Funcionario");
	fopen_s(&p_funcionario, "funcionarios.txt", "r");

	if (p_funcionario != NULL) {

		while (!feof(p_funcionario)) {
			fread(&info_funcionario, sizeof(funcionario_t), 1, p_funcionario);

			if (info_funcionario.id == novo_funcionario.id) {
				printf("\n");
				mostra_funcionario(info_funcionario);

				printf("Este ID ja esta em uso!\n");

				rewind(p_funcionario);

				getchar();
				limpa_tela();

				return;
			}
		}

		fclose(p_funcionario);
	}

	recebe_nome(novo_funcionario.nome, "do Funcionario");

	novo_funcionario.genero = recebe_genero();

	novo_funcionario.data = recebe_data(novo_funcionario.data);

	recebe_string(novo_funcionario.pais, "Pais");

	recebe_string(novo_funcionario.funcao, "Funcao");

	recebe_string(novo_funcionario.especialidade, "Especialidade");

	recebe_string(novo_funcionario.especialidade, "Alojamento");

	novo_funcionario.voluntario = recebe_bool("É voluntario");

	limpa_tela();
	mostra_funcionario(novo_funcionario);

	printf("\nOs dados estao corretos?\n1 = Sim / 0 = Nao\n>>>   ");
	scanf_s("%d%*c", &manter);

	do {
		switch (manter) {
		case 0:
			printf("Descartando informacoes...\n");
			break;
		case 1:
			fopen_s(&p_funcionario, "funcionarios.txt", "a");
			if (p_funcionario == NULL) {
				printf("Erro ao abrir arquivo!\n");
				exit(EXIT_FAILURE);
			}
			fwrite(&novo_funcionario, sizeof(funcionario_t), 1, p_funcionario);
			fclose(p_funcionario);
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

void calendario_treinos() {
	evento_t info_treino;
	FILE *p_treinos;

	fopen_s(&p_treinos, "treinos.txt", "r");

	if (!p_treinos) {
		printf("Nenhum cadastro foi encontrado!\n");

		getchar();
		limpa_tela();

		return;
	}

	memset(&info_treino, 0, sizeof(treino_t));

	do {
		fread(&info_treino, sizeof(treino_t), 1, p_treinos);
		if (feof(p_treinos)) {
			break;
		}
		mostra_evento(info_treino);
		printf("\n\n");
	} while (!feof(p_treinos));

	fclose(p_treinos);

	getchar();
	limpa_tela();
}
 
void agenda_treino() {
	int manter;
	treino_t novo_treino, info_treino;
	FILE* p_treinos;

	printf("Insira as informacoes do treino:\n");

	recebe_nome(novo_treino.local, "do Local");

	novo_treino.data = recebe_data();

	fopen_s(&p_treinos, "treinos.txt", "r");

	if (p_treinos != NULL) {

		while (!feof(p_treinos)) {
			fread(&info_treino, sizeof(treino_t), 1, p_treinos);

			if (!strcmp(info_treino.local, novo_treino.local) &&
				!compara_datas(info_treino.data, novo_treino.data)) {
				printf("\n");
				mostra_treino(info_treino);

				printf("\nHorario ocupado!\n");

				rewind(p_treinos);

				getchar();
				limpa_tela();

				return;
			}
		}

		fclose(p_treinos);
	}

	limpa_tela();
	mostra_treino(novo_treino);

	printf("\nOs dados estao corretos?\n1 = Sim / 0 = Nao\n>>>   ");
	scanf_s("%d%*c", &manter);

	do {
		switch (manter) {
		case 0:
			printf("Descartando informacoes...\n");
			break;
		case 1:
			fopen_s(&p_treinos, "treinos.txt", "a");
			if (p_treinos == NULL) {
				printf("Erro ao abrir arquivo!\n");
				exit(EXIT_FAILURE);
			}
			fwrite(&novo_treino, sizeof(treino_t), 1, p_treinos);
			fclose(p_treinos);
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

void calendario_eventos() {
	evento_t info_evento;
	FILE *p_eventos;

	fopen_s(&p_eventos, "eventos.txt", "r");

	if (!p_eventos) {
		printf("Nenhum cadastro foi encontrado!\n");

		getchar();
		limpa_tela();

		return;
	}

	memset(&info_evento, 0, sizeof(evento_t));

	do {
		fread(&info_evento, sizeof(evento_t), 1, p_eventos);
		if (feof(p_eventos)) {
			break;
		}
		mostra_evento(info_evento);
		printf("\n\n");
	} while (!feof(p_eventos));

	fclose(p_eventos);

	getchar();
	limpa_tela();
}

void cadastra_evento() {
	int manter;
	evento_t novo_evento, info_evento;
	FILE* p_eventos;

	memset(&novo_evento, 0, sizeof(evento_t));
	memset(&info_evento, 0, sizeof(evento_t));

	printf("Insira as informacoes:\n\n");

	recebe_nome(novo_evento.nome, "do Local");

	recebe_nome(novo_evento.cidade, "da Cidade");

	novo_evento.data = recebe_data();

	fopen_s(&p_eventos, "eventos.txt", "r");

	if (p_eventos != NULL) {

		while (!feof(p_eventos)) {
			fread(&info_evento, sizeof(evento_t), 1, p_eventos);

			if (!strcmp(info_evento.nome, novo_evento.nome) &&
				!compara_datas(info_evento.data, novo_evento.data)) {
				printf("\n");
				mostra_evento(info_evento);

				printf("\nHorario ocupado!\n");

				rewind(p_eventos);

				getchar();
				limpa_tela();

				return;
			}
		}

		fclose(p_eventos);
	}

	recebe_string(novo_evento.participantes, "Participantes");

	recebe_string(novo_evento.modalidade, "Modalidade");

	recebe_string(novo_evento.equipamentos, "Equipamentos Necessarios");

	novo_evento.capacidade = recebe_inteiro("Capacidade");

	limpa_tela();
	mostra_evento(novo_evento);

	printf("\nOs dados estao corretos?\n1 = Sim / 0 = Nao\n>>>   ");
	scanf_s("%d%*c", &manter);

	do {
		switch (manter) {
		case 0:
			printf("Descartando informacoes...\n");
			break;
		case 1:
			fopen_s(&p_eventos, "eventos.txt", "a");
			if (p_eventos == NULL) {
				printf("Erro ao abrir arquivo!\n");
				exit(EXIT_FAILURE);
			}
			fwrite(&novo_evento, sizeof(evento_t), 1, p_eventos);
			fclose(p_eventos);
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

void medalha_atleta() {
	int manter, id;
	bool encontrado = false;
	atleta_t info_atleta;
	FILE *p_atletas;

	fopen_s(&p_atletas, "atletas.txt", "r");

	if (!p_atletas) {
		printf("Nenhum cadastro foi encontrado!\n");

		getchar();
		limpa_tela();

		return;
	}

	memset(&info_atleta, 0, sizeof(atleta_t));

	printf("\nInsira o ID do atleta desejado: ");
	id = recebe_id();

	while (!feof(p_atletas)) {
		fread(&info_atleta, sizeof(atleta_t), 1, p_atletas);

		if (id == info_atleta.id) {
			printf("\n");
			mostra_atleta(info_atleta);

			encontrado = true;

			printf("\n1 - Ouro\n2 - Prata\n3 - Bronze\n>>>   ");
			scanf_s("%d%*c", &manter);

			do {
				switch (manter) {
					case 0:
						break;
					case 1:
						fopen_s(&p_atletas, "atletas.txt", "a");
						if (p_atletas == NULL) {
							printf("Erro ao abrir arquivo!\n");
							exit(EXIT_FAILURE);
						}
						info_atleta.medalhas.ouro = recebe_inteiro("Ouro");
						fwrite(&info_atleta, sizeof(atleta_t), 1, p_atletas);
						fclose(p_atletas);
						printf("Medalha adicionada!\n");
						break;
					case 2:
						fopen_s(&p_atletas, "atletas.txt", "a");
						if (p_atletas == NULL) {
							printf("Erro ao abrir arquivo!\n");
							exit(EXIT_FAILURE);
						}
						info_atleta.medalhas.prata = recebe_inteiro("Prata");
						fwrite(&info_atleta, sizeof(atleta_t), 1, p_atletas);
						fclose(p_atletas);
						printf("Medalha adicionada!\n");
						break;
					case 3:
						fopen_s(&p_atletas, "atletas.txt", "a");
						if (p_atletas == NULL) {
							printf("Erro ao abrir arquivo!\n");
							exit(EXIT_FAILURE);
						}
						info_atleta.medalhas.bronze = recebe_inteiro("Bronze");
						fwrite(&info_atleta, sizeof(atleta_t), 1, p_atletas);
						fclose(p_atletas);
						printf("Medalha adicionada!\n");
						break;
					default:
						printf("\nOpcao invalida, tente novamente!\n");
						break;
				}
			} while (manter != 0 && manter != 1);

			rewind(p_atletas);

			getchar();
			limpa_tela();

			break;
		}
	}

	if (!encontrado) {
		printf("\Equipe nao foi encontrado!\n");

		getchar();
		limpa_tela();
	}

	fclose(p_atletas);
}

void lista_atletas() {
	atleta_t info_atleta;
	FILE* p_atletas;

	fopen_s(&p_atletas, "atletas.txt", "r");

	if (!p_atletas) {
		printf("Nenhum cadastro foi encontrado!\n");

		getchar();
		limpa_tela();

		return;
	}

	memset(&info_atleta, 0, sizeof(atleta_t));

	do {
		fread(&info_atleta, sizeof(atleta_t), 1, p_atletas);
		if (feof(p_atletas)) {
			break;
		}
		mostra_atleta(info_atleta);
	} while (!feof(p_atletas));

	fclose(p_atletas);

	getchar();
	limpa_tela();
}

void busca_atleta() {
	int manter, id;
	bool encontrado = false;
	atleta_t info_atleta;
	FILE* p_atletas;

	fopen_s(&p_atletas, "atletas.txt", "r");

	if (!p_atletas) {
		printf("Nenhum cadastro foi encontrado!\n");

		getchar();
		limpa_tela();

		return;
	}

	memset(&info_atleta, 0, sizeof(atleta_t));

	printf("\nInsira o ID do atleta desejado: ");
	id = recebe_id();

	while (!feof(p_atletas)) {
		fread(&info_atleta, sizeof(atleta_t), 1, p_atletas);

		if (id == info_atleta.id) {
			printf("\n");
			mostra_atleta(info_atleta);

			encontrado = true;

			printf("\nDeseja excluir?\n1 = Sim / 0 = Nao\n>>>   ");
			scanf_s("%d%*c", &manter);

			do {
				switch (manter) {
				case 0:
					break;
				case 1:
					fopen_s(&p_atletas, "atletas.txt", "a");
					if (p_atletas == NULL) {
						printf("Erro ao abrir arquivo!\n");
						exit(EXIT_FAILURE);
					}
					memset(&info_atleta, 0, sizeof(atleta_t));
					fwrite(&info_atleta, sizeof(atleta_t), 1, p_atletas);
					fclose(p_atletas);
					printf("Item Removido!\n");
					break;
				default:
					printf("\nOpcao invalida, tente novamente!\n");
					break;
				}
			} while (manter != 0 && manter != 1);

			rewind(p_atletas);

			getchar();
			limpa_tela();

			break;
		}
	}

	if (!encontrado) {
		printf("\nAtleta nao foi encontrado!\n");

		getchar();
		limpa_tela();
	}

	fclose(p_atletas);
}

void cadastra_atleta() {
	int manter;
	atleta_t novo_atleta, info_atleta;
	FILE* p_atletas;

	memset(&novo_atleta, 0, sizeof(atleta_t));
	memset(&info_atleta, 0, sizeof(atleta_t));

	printf("Insira as informacoes:\n\n");

	novo_atleta.id = recebe_id();
	fopen_s(&p_atletas, "atletas.txt", "r");

	if (p_atletas != NULL) {

		while (!feof(p_atletas)) {
			fread(&info_atleta, sizeof(atleta_t), 1, p_atletas);

			if (info_atleta.id == novo_atleta.id) {
				printf("\n");
				mostra_atleta(info_atleta);

				printf("Este ID ja esta em uso!\n");

				rewind(p_atletas);

				getchar();
				limpa_tela();

				return;
			}
		}

		fclose(p_atletas);
	}

	recebe_nome(novo_atleta.nome, "do Atleta");
	
	novo_atleta.genero = recebe_genero();

	novo_atleta.data = recebe_data();

	novo_atleta.naturalidade = recebe_local();

	recebe_string(novo_atleta.modalidade, "Modalidade");

	recebe_string(novo_atleta.alojamento, "Alojamento");

	novo_atleta.altura = recebe_flutuante("Altura");

	novo_atleta.peso = recebe_flutuante("Peso");

	novo_atleta.vacina = recebe_bool("Vacinado contra o COVID-19");

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

void medalha_equipe() {
	int manter, id;
	bool encontrado = false;
	equipe_t info_equipe;
	FILE *p_equipes;

	fopen_s(&p_equipes, "equipes.txt", "r");

	if (!p_equipes) {
		printf("Nenhum cadastro foi encontrado!\n");

		getchar();
		limpa_tela();

		return;
	}

	memset(&info_equipe, 0, sizeof(equipe_t));

	printf("\nInsira o ID da equipe desejada: ");
	id = recebe_id();

	while (!feof(p_equipes)) {
		fread(&info_equipe, sizeof(equipe_t), 1, p_equipes);

		if (id == info_equipe.id) {
			printf("\n");
			mostra_equipe(info_equipe);

			encontrado = true;

			printf("\n1 - Ouro\n2 - Prata\n3 - Bronze\n>>>   ");
			scanf_s("%d%*c", &manter);

			do {
				switch (manter) {
					case 0:
						break;
					case 1:
						fopen_s(&p_equipes, "equipes.txt", "a");
						if (p_equipes == NULL) {
							printf("Erro ao abrir arquivo!\n");
							exit(EXIT_FAILURE);
						}
						info_equipe.medalhas.ouro = recebe_inteiro("Ouro");
						fwrite(&info_equipe, sizeof(equipe_t), 1, p_equipes);
						fclose(p_equipes);
						printf("Medalha adicionada!\n");
						break;
					case 2:
						fopen_s(&p_equipes, "equipes.txt", "a");
						if (p_equipes == NULL) {
							printf("Erro ao abrir arquivo!\n");
							exit(EXIT_FAILURE);
						}
						info_equipe.medalhas.prata = recebe_inteiro("Prata");
						fwrite(&info_equipe, sizeof(equipe_t), 1, p_equipes);
						fclose(p_equipes);
						printf("Medalha adicionada!\n");
						break;
					case 3:
						fopen_s(&p_equipes, "equipes.txt", "a");
						if (p_equipes == NULL) {
							printf("Erro ao abrir arquivo!\n");
							exit(EXIT_FAILURE);
						}
						info_equipe.medalhas.bronze = recebe_inteiro("Bronze");
						fwrite(&info_equipe, sizeof(equipe_t), 1, p_equipes);
						fclose(p_equipes);
						printf("Medalha adicionada!\n");
						break;
					default:
						printf("\nOpcao invalida, tente novamente!\n");
						break;
				}
			} while (manter != 0 && manter != 1);

			rewind(p_equipes);

			getchar();
			limpa_tela();

			break;
		}
	}

	if (!encontrado) {
		printf("\Equipe nao foi encontrado!\n");

		getchar();
		limpa_tela();
	}

	fclose(p_equipes);
}

void lista_equipes() {
	equipe_t info_equipe;
	FILE *p_equipes;

	fopen_s(&p_equipes, "equipes.txt", "r");

	if (!p_equipes) {
		printf("Nenhum cadastro foi encontrado!\n");

		getchar();
		limpa_tela();

		return;
	}

	memset(&info_equipe, 0, sizeof(equipe_t));

	do {
		fread(&info_equipe, sizeof(equipe_t), 1, p_equipes);
		if (feof(p_equipes)) {
			break;
		}
		mostra_equipe(info_equipe);
	} while (!feof(p_equipes));

	fclose(p_equipes);

	getchar();
	limpa_tela();
}

void busca_equipe() {
	int manter, id;
	bool encontrado = false;
	equipe_t info_equipe;
	FILE* p_equipes;

	fopen_s(&p_equipes, "equipes.txt", "r");

	if (!p_equipes) {
		printf("Nenhum cadastro foi encontrado!\n");

		getchar();
		limpa_tela();

		return;
	}

	memset(&info_equipe, 0, sizeof(equipe_t));

	printf("\nInsira o ID da equipe desejada: ");
	id = recebe_id();

	while (!feof(p_equipes)) {
		fread(&info_equipe, sizeof(equipe_t), 1, p_equipes);

		if (id == info_equipe.id) {
			printf("\n");
			mostra_equipe(info_equipe);

			encontrado = true;

			printf("\nDeseja excluir?\n1 = Sim / 0 = Nao\n>>>   ");
			scanf_s("%d%*c", &manter);

			do {
				switch (manter) {
				case 0:
					break;
				case 1:
					fopen_s(&p_equipes, "equipes.txt", "a");
					if (p_equipes == NULL) {
						printf("Erro ao abrir arquivo!\n");
						exit(EXIT_FAILURE);
					}
					memset(&info_equipe, 0, sizeof(equipe_t));
					fwrite(&info_equipe, sizeof(equipe_t), 1, p_equipes);
					fclose(p_equipes);
					printf("Item Removido!\n");
					break;
				default:
					printf("\nOpcao invalida, tente novamente!\n");
					break;
				}
			} while (manter != 0 && manter != 1);

			rewind(p_equipes);

			getchar();
			limpa_tela();

			break;
		}
	}

	if (!encontrado) {
		printf("\Equipe nao foi encontrado!\n");

		getchar();
		limpa_tela();
	}

	fclose(p_equipes);
}

void cadastra_equipe() {
	int manter;
	equipe_t nova_equipe, info_equipe;
	FILE* p_equipes;

	memset(&nova_equipe, 0, sizeof(equipe_t));
	memset(&info_equipe, 0, sizeof(equipe_t));

	printf("Insira as informacoes:\n\n");

	nova_equipe.id = recebe_id();

	fopen_s(&p_equipes, "equipes.txt", "r");

	if (p_equipes != NULL) {

		while (!feof(p_equipes)) {
			fread(&info_equipe, sizeof(equipe_t), 1, p_equipes);

			if (info_equipe.id == nova_equipe.id) {
				printf("\n");
				mostra_equipe(info_equipe);

				printf("Este ID ja esta em uso!\n");

				rewind(p_equipes);

				getchar();
				limpa_tela();

				return;
			}
		}

		fclose(p_equipes);
	}

	recebe_nome(nova_equipe.nome, "Nome da Equipe");

	recebe_nome(nova_equipe.pais, "do Pais");

	recebe_string(nova_equipe.modalidade, "Modalidade");

	limpa_tela();
	mostra_equipe(nova_equipe);

	printf("\nOs dados estao corretos?\n1 = Sim / 0 = Nao\n>>>   ");
	scanf_s("%d%*c", &manter);

	do {
		switch (manter) {
		case 0:
			printf("Descartando informacoes...\n");
			break;
		case 1:
			fopen_s(&p_equipes, "equipes.txt", "a");
			if (p_equipes == NULL) {
				printf("Erro ao abrir arquivo!\n");
				exit(EXIT_FAILURE);
			}
			fwrite(&nova_equipe, sizeof(atleta_t), 1, p_equipes);
			fclose(p_equipes);
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

/* MENUS */

/* Todos os menus seguirão este modelo de menu switch, foi o jeito mais facil
 * que encontrei, mas com certeza deve ter um jeito em que não seria
 * necessário criar um menu específico para cada tela.
 */

void menu_funcionarios() {
	int menu_opcao;

	do {
		printf(" _______________ MENU CADASTROS _______________\n");
		printf("|                                              |\n");
		printf("|         Selecione uma das opcoes:            |\n");
		printf("|   1 - Adicionar                              |\n");
		printf("|   2 - Buscar                                 |\n");
		printf("|   3 - Listar                                 |\n");
		printf("|   0 - Voltar                                 |\n");
		printf("|______________________________________________|\n>>>  ");
		scanf_s("%d%*c", &menu_opcao);

		switch (menu_opcao) {
			case 1:
				limpa_tela();
				cadastra_funcionario();
				break;
			case 2:
				limpa_tela();
				busca_funcionario();
				break;
			case 3:
				limpa_tela();
				lista_funcionarios();
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

void menu_treinos() {
	int menu_opcao;

	do {
		printf(" _______________ MENU CADASTROS _______________\n");
		printf("|                                              |\n");
		printf("|         Selecione uma das opcoes:            |\n");
		printf("|   1 - Agendar                                |\n");
		printf("|   2 - Calendario                             |\n");
		printf("|   0 - Voltar                                 |\n");
		printf("|______________________________________________|\n>>>  ");
		scanf_s("%d%*c", &menu_opcao);

		switch (menu_opcao) {
			case 1:
				limpa_tela();
				agenda_treino();
				break;
			case 2:
				limpa_tela();
				calendario_treinos;
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

void menu_eventos() {
	int menu_opcao;

	do {
		printf(" _______________ MENU CADASTROS _______________\n");
		printf("|                                              |\n");
		printf("|         Selecione uma das opcoes:            |\n");
		printf("|   1 - Agendar                                |\n");
		printf("|   2 - Calendario                             |\n");
		printf("|   0 - Voltar                                 |\n");
		printf("|______________________________________________|\n>>>  ");
		scanf_s("%d%*c", &menu_opcao);

		switch (menu_opcao) {
			case 1:
				limpa_tela();
				cadastra_evento();
				break;
			case 2:
				limpa_tela();
				calendario_eventos();
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

void menu_atletas() {
	int menu_opcao;

	do {
		printf(" _______________ MENU CADASTROS _______________\n");
		printf("|                                              |\n");
		printf("|         Selecione uma das opcoes:            |\n");
		printf("|   1 - Adicionar Atleta                       |\n");
		printf("|   2 - Buscar                                 |\n");
		printf("|   3 - Listar                                 |\n");
		printf("|   4 - Adicionar Medalha                      |\n");
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
			busca_atleta();
			break;
		case 3:
			limpa_tela();
			lista_atletas();
			break;
		case 4:
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

void menu_equipes() {
	int menu_opcao;

	do {
		printf(" _______________ MENU CADASTROS _______________\n");
		printf("|                                              |\n");
		printf("|         Selecione uma das opcoes:            |\n");
		printf("|   1 - Adicionar                              |\n");
		printf("|   2 - Buscar                                 |\n");
		printf("|   3 - Listar                                 |\n");
		printf("|   4 - Adicionar Medalha                      |\n");
		printf("|   0 - Voltar                                 |\n");
		printf("|______________________________________________|\n>>>  ");
		scanf_s("%d%*c", &menu_opcao);

		switch (menu_opcao) {
			case 1:
				limpa_tela();
				cadastra_equipe();
				break;
			case 2:
				limpa_tela();
				busca_equipe();
				break;
			case 3:
				limpa_tela();
				lista_equipes();
				break;
			case 4:
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

void menu_relatorios() {
	int menu_opcao;

	do {
		printf(" _______________ MENU RELATORIOS ______________\n");
		printf("|                                              |\n");
		printf("|         Selecione uma das opcoes:            |\n");
		printf("|   1 - Contagem de Medalhas                   |\n");
		printf("|   2 - Medalhistas                            |\n");
		printf("|   3 - Total de Medalhas Distribuidas         |\n");
		printf("|   0 - Voltar                                 |\n");
		printf("|______________________________________________|\n>>>  ");
		scanf_s("%d%*c", &menu_opcao);

		switch (menu_opcao) {
		case 1:
			limpa_tela();
			printf("Opcao 1");
			break;
		case 2:
			printf("Opcao 2");
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
	} while (menu_opcao != 0);
}

void menu_cadastros() {
	int menu_opcao;

	do {
		printf(" _______________ MENU CADASTROS _______________\n");
		printf("|                                              |\n");
		printf("|         Selecione uma das opcoes:            |\n");
		printf("|   1 - Equipes                                |\n");
		printf("|   2 - Atletas                                |\n");
		printf("|   3 - Eventos                                |\n");
		printf("|   4 - Agendar Treino                         |\n");
		printf("|   5 - Funcionarios                           |\n");
		printf("|   0 - Voltar                                 |\n");
		printf("|______________________________________________|\n>>>  ");
		scanf_s("%d%*c", &menu_opcao);

		switch (menu_opcao) {
		case 1:
			limpa_tela();
			menu_equipes();
			break;
		case 2:
			limpa_tela();
			menu_atletas();
			break;
		case 3:
			limpa_tela();
			menu_eventos();
			break;
		case 4:
			limpa_tela();
			menu_treinos();
			break;
		case 5:
			limpa_tela();
			menu_funcionarios();
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

void menu_inicial() {
	int menu_opcao;

	do {
		printf(" ________________ MENU INICIAL ________________\n");
		printf("|                                              |\n");
		printf("|          Selecione uma das opcoes:           |\n");
		printf("|   1 - Cadastros                              |\n");
		printf("|   2 - Relatorios                             |\n");
		printf("|   3 - Alterar Logins                         |\n");
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

/* MAIN */

int main(int argc, char *argv[]) {
	printf(" ______________________________________________\n");
	printf("|                                              |\n");
	printf("|                                              |\n");
	printf("|                                              |\n");
	printf("|   Bem-vindo ao aplicativo de gerenciamento   |\n");
	printf("|       das Olimpiadas de Paris de 2024!       |\n");
	printf("|                                              |\n");
	printf("|                                              |\n");
	printf("|        Pressione Enter para Continuar        |\n");
	printf("|______________________________________________|\n");

	getchar();
	limpa_tela();

	login();

	menu_inicial();

	return EXIT_SUCCESS;
}

/* FIM */