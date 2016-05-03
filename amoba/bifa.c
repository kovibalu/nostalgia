#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bifa.h"

static unsigned zobalap = 0x80000000U;
/* Zobrist-hasing ertektablaja: [sor][oszlop][jatekos] */
unsigned zobtabla[16][16][3] = {
	{
		{0, 0x045F8166U, 0x2DA4172CU},
		{0, 0xBAA7F46EU, 0xEAC8578BU},
		{0, 0xEC747744U, 0xF525CA13U},
		{0, 0xFF1642F4U, 0xDA6ADA86U},
		{0, 0x5A696C35U, 0x590AFA03U},
		{0, 0x13E6C7D8U, 0xCDA6EAD1U},
		{0, 0x2E4230E1U, 0xD96A3333U},
		{0, 0xCAD6508CU, 0x05442C7DU},
		{0, 0x1AFE35FCU, 0xDA634B21U},
		{0, 0x6F71C8C7U, 0x8B908DFAU},
		{0, 0x8529A52DU, 0xDCA5618BU},
		{0, 0x222EC386U, 0x01C37B95U},
		{0, 0xC4FA5913U, 0xBF9D862EU},
		{0, 0xE584FBB5U, 0xA0FB0590U},
		{0, 0x4BC8D280U, 0x329AB085U},
		{0, 0xE3EEC15EU, 0x9FC79C71U},
	},
	{
		{0, 0x847904BFU, 0x1E6C74CCU},
		{0, 0xB332B6A8U, 0xEBAEC237U},
		{0, 0x6423EADBU, 0xE79CA079U},
		{0, 0x08F72854U, 0x97544F9DU},
		{0, 0x5357C108U, 0x6ADABA21U},
		{0, 0x24138E38U, 0x80E15F6CU},
		{0, 0x32BD8D7CU, 0x3DA279D7U},
		{0, 0xDD7202ECU, 0xCB62AB62U},
		{0, 0x509DC0B1U, 0x68BB00C1U},
		{0, 0xD1BD82A4U, 0x56F728C1U},
		{0, 0x05732126U, 0xEF64232BU},
		{0, 0x034FAB62U, 0x8BB0D7ABU},
		{0, 0xCFF1E488U, 0x3EB5CCCCU},
		{0, 0x5054B054U, 0xE99D908DU},
		{0, 0x91E747DFU, 0x051AFA65U},
		{0, 0x160389BEU, 0x55D82BE8U},
	},
	{
		{0, 0x4A2EF2A0U, 0xA1FC3EAEU},
		{0, 0x04FACE09U, 0x35AD7728U},
		{0, 0x280C5F87U, 0x00CCF8B9U},
		{0, 0x3A6F6AB2U, 0x5513F2A0U},
		{0, 0x9D505496U, 0x9C63F0E1U},
		{0, 0xC69BFC7BU, 0x0CDEFF73U},
		{0, 0xF0BB0A23U, 0x0E7F19B4U},
		{0, 0x3FAB284EU, 0xC25D1AFFU},
		{0, 0xDD234FAAU, 0x15FA4223U},
		{0, 0xA28DB044U, 0x5C49B5DCU},
		{0, 0xC954927BU, 0x13FC79CDU},
		{0, 0x3497F120U, 0xC79642B6U},
		{0, 0x0307D595U, 0x496486A8U},
		{0, 0x239DCAB6U, 0x2D862D96U},
		{0, 0x9CC170C6U, 0xBDC790C6U},
		{0, 0x2513EBDCU, 0x78BAA6F7U},
	},
	{
		{0, 0x03844FBDU, 0xC315160AU},
		{0, 0x7603846BU, 0xFD12CA31U},
		{0, 0xA19AD89CU, 0x3B24BA5FU},
		{0, 0xCFAE3352U, 0xD92D75FFU},
		{0, 0xBDA7E18FU, 0xADA38A07U},
		{0, 0xF1CAB69BU, 0x44F8626EU},
		{0, 0xBD88BF1EU, 0xD15F1254U},
		{0, 0x0C6B63AEU, 0x261AA6E0U},
		{0, 0x9524FA37U, 0x06423867U},
		{0, 0x8744FAA6U, 0x984A01C3U},
		{0, 0x84EA2F4CU, 0x201D10ADU},
		{0, 0xE61A9280U, 0x4E89F56DU},
		{0, 0xEB085182U, 0xFBE8764AU},
		{0, 0xBD258A96U, 0xB7E0BA0BU},
		{0, 0x549EFC79U, 0xDA37C386U},
		{0, 0x93EBA038U, 0xB09D13EAU},
	},
	{
		{0, 0x8FB3CA22U, 0x76C144E8U},
		{0, 0xC183C78FU, 0xD0744DEEU},
		{0, 0xD7F16521U, 0x8BBDD1BFU},
		{0, 0xECD25932U, 0x90CEC062U},
		{0, 0x708D7ED0U, 0x0ADF41E7U},
		{0, 0x4862FC7DU, 0xFBBFD5BCU},
		{0, 0x15E60285U, 0xE38748B2U},
		{0, 0xF1D233E8U, 0x3EA423F0U},
		{0, 0x415A4E08U, 0xA08F7085U},
		{0, 0x3594B3E2U, 0xF134961EU},
		{0, 0x3EADAAD1U, 0xC741524FU},
		{0, 0xDBEAD862U, 0x1A6F2870U},
		{0, 0xF62EEEDFU, 0x86193DEAU},
		{0, 0xDEE5A070U, 0xDA7F9E54U},
		{0, 0x78B94964U, 0xE9BEAB60U},
		{0, 0xF82ADADAU, 0x6C02A6F5U},
	},
	{
		{0, 0xD7FC7F1AU, 0x05C80E08U},
		{0, 0xB0FBAD7DU, 0x186BF8F3U},
		{0, 0x1FC7913EU, 0xFC799B9DU},
		{0, 0x52525BD0U, 0x0CD9BC79U},
		{0, 0x2A9ADB4DU, 0x70560385U},
		{0, 0x3AB79C1DU, 0xBB0540A1U},
		{0, 0xD9F1D799U, 0x56462AD2U},
		{0, 0xC31A5908U, 0xF1A7944FU},
		{0, 0xCA79C317U, 0xD37F1265U},
		{0, 0x6239C150U, 0x7D333305U},
		{0, 0x729A5FCAU, 0xD7C1088FU},
		{0, 0x38239006U, 0xD0508D7FU},
		{0, 0x30517B44U, 0xA5D15720U},
		{0, 0xEBF8FAB8U, 0x5258235DU},
		{0, 0xBB0BBC7FU, 0x1F46E180U},
		{0, 0xEDB698FAU, 0x6764214CU},
	},
	{
		{0, 0x58CAC005U, 0xB7386462U},
		{0, 0x162EF515U, 0x1E4964ECU},
		{0, 0x12C80423U, 0xCF80AB69U},
		{0, 0x218B0515U, 0x46F72964U},
		{0, 0xA6F42F52U, 0xE7862B6DU},
		{0, 0x8D5FC6F7U, 0x7702EDBEU},
		{0, 0xC25F7186U, 0x35FE6660U},
		{0, 0x740E13EAU, 0xBDD90952U},
		{0, 0x866F740EU, 0x66F758CBU},
		{0, 0xD9E18BB8U, 0xA7448E18U},
		{0, 0xF3F0E8D7U, 0x603862F9U},
		{0, 0x0E93E6E5U, 0xDD5338E6U},
		{0, 0x38529E59U, 0x13E10544U},
		{0, 0x591838DAU, 0x1E22B642U},
		{0, 0xE7442362U, 0x2E02A7F2U},
		{0, 0x1F57D018U, 0xA37F9D13U},
	},
	{
		{0, 0x18855590U, 0x90E13586U},
		{0, 0x2DA6B7F7U, 0xC716C17FU},
		{0, 0xDAAEABB8U, 0x2900E18BU},
		{0, 0x14236D37U, 0xAB908CFAU},
		{0, 0xEFC3B25BU, 0x966F718BU},
		{0, 0xEEC72D57U, 0x7E7D5823U},
		{0, 0x0E2CCC13U, 0x833B1CA0U},
		{0, 0x17E7510EU, 0x35FEBC09U},
		{0, 0x2E00E191U, 0x1CA603ABU},
		{0, 0xADA1E1DAU, 0xAAEA1B86U},
		{0, 0xBFE7F449U, 0x13E02259U},
		{0, 0xBDCBAC0DU, 0x352DA6F1U},
		{0, 0xF5E42347U, 0x60284DA6U},
		{0, 0x2EC1513EU, 0xDD2511DFU},
		{0, 0x6F7286EDU, 0xB99BDD1EU},
		{0, 0x28CFEADCU, 0xAB59080EU},
	},
	{
		{0, 0xF42771CBU, 0xC9697F46U},
		{0, 0x5A579D33U, 0x8BB07662U},
		{0, 0x54993EA5U, 0x1058ABEAU},
		{0, 0xD6F62FDFU, 0xAB8A33E7U},
		{0, 0x6B491564U, 0x30FB13ABU},
		{0, 0x7A866FB1U, 0xB05B8E18U},
		{0, 0x4A235908U, 0xF8E35E4EU},
		{0, 0xA337296CU, 0x78A91994U},
		{0, 0x639754CCU, 0xAB4A2349U},
		{0, 0x0E18A13EU, 0x62E9FCBFU},
		{0, 0x65495110U, 0xAD4548BAU},
		{0, 0xCC4EE66FU, 0xB90A03ECU},
		{0, 0xBD8BB4FEU, 0xD5F42746U},
		{0, 0x9D511BDCU, 0xC113ECE0U},
		{0, 0xA25D13B0U, 0xD37BD5FCU},
		{0, 0x9B87A83EU, 0x6626BD91U},
	},
	{
		{0, 0xFD10ECD6U, 0x7F9D1524U},
		{0, 0xEA9FC791U, 0x078FAB5DU},
		{0, 0x0D128BFAU, 0xA7BDD928U},
		{0, 0xE13EC539U, 0x75ADA6DCU},
		{0, 0xB13EA0F9U, 0x03B35968U},
		{0, 0x417E37D1U, 0x28422305U},
		{0, 0xC345FC55U, 0xC9CB152EU},
		{0, 0xD08EE2CCU, 0xEA01078BU},
		{0, 0xB1BDF9D3U, 0x88DB69B8U},
		{0, 0x39DCFBDCU, 0x2697C0A0U},
		{0, 0x683EC40FU, 0xCC9D13DEU},
		{0, 0x7AB657ABU, 0xE29C96D3U},
		{0, 0x239D10E1U, 0x87456525U},
		{0, 0xF1BD693CU, 0x097C79F8U},
		{0, 0xA80EAFABU, 0x64A2B65CU},
		{0, 0xF776635EU, 0x3CA05289U},
	},
	{
		{0, 0x235E5B49U, 0x0CD45795U},
		{0, 0xBD82A4F1U, 0x4CC80E40U},
		{0, 0xC96426E7U, 0xF52590CCU},
		{0, 0x5A0E9E59U, 0x7C520301U},
		{0, 0xFC193DE6U, 0x7C42008CU},
		{0, 0x36FB1D13U, 0x6DA4B61AU},
		{0, 0x8D7261CAU, 0x6F1A7FCCU},
		{0, 0xCF4A802EU, 0x2626F296U},
		{0, 0xBDCA6E4AU, 0x7C1333DEU},
		{0, 0xC925903CU, 0xADB0553DU},
		{0, 0xA0347B92U, 0xFBDD113CU},
		{0, 0x117F1D09U, 0x26F7230AU},
		{0, 0x62B68DFCU, 0x288D5EC1U},
		{0, 0x42E4231EU, 0x04FBCD2FU},
		{0, 0x7CA00817U, 0x1526EC1EU},
		{0, 0x44FA0BB8U, 0xB097C79EU},
	},
	{
		{0, 0xAB69FE54U, 0xBB642F73U},
		{0, 0x1E62EC13U, 0xD0FA9B9BU},
		{0, 0xC16BB054U, 0x42ECFAEEU},
		{0, 0x2EC7DEBBU, 0xB0549F1EU},
		{0, 0x745788B7U, 0xCCCA62EEU},
		{0, 0x84235FF7U, 0xA59303C3U},
		{0, 0x15FCD6F3U, 0x1CE6272CU},
		{0, 0x7F12DA6AU, 0x4F78578DU},
		{0, 0x70C49A54U, 0x4FAB511EU},
		{0, 0xFAB5DA7AU, 0xF1AFE062U},
		{0, 0x2E03DEADU, 0x496479DCU},
		{0, 0x06EF7769U, 0x2EE19C15U},
		{0, 0xCEC13823U, 0x1BDC1663U},
		{0, 0x55446BFAU, 0xCEC14832U},
		{0, 0x35B79D08U, 0xA35EA6FAU},
		{0, 0x332B5959U, 0xD1FC7203U},
	},
	{
		{0, 0xE642236FU, 0x9BAD6513U},
		{0, 0x20BAA6F7U, 0x10D52496U},
		{0, 0x0E5D0549U, 0x231CB00EU},
		{0, 0x9D37B45BU, 0x7C632807U},
		{0, 0x18608E28U, 0xBF33280EU},
		{0, 0xE1C31595U, 0xABDDBCDCU},
		{0, 0x588FF2ECU, 0x8B67454AU},
		{0, 0x18BBD289U, 0xC35FCA00U},
		{0, 0x78F33769U, 0x18FE1BFCU},
		{0, 0x85FCEADAU, 0x594D6F7BU},
		{0, 0x4F444BB6U, 0x3EA423BEU},
		{0, 0xB683358FU, 0xE38E1909U},
		{0, 0x064F8F3AU, 0xEF705423U},
		{0, 0xA79D1918U, 0x23A6F72DU},
		{0, 0x99D12C15U, 0x80D7CE18U},
		{0, 0x81C3337BU, 0x5DEAFE38U},
	},
	{
		{0, 0x24949672U, 0x6439E7F1U},
		{0, 0xD11BDC96U, 0x7D039088U},
		{0, 0x2236B856U, 0x9510E2ECU},
		{0, 0xFAAAEEBDU, 0x7F299918U},
		{0, 0x93EA3B35U, 0x18F762ECU},
		{0, 0x52DA6C74U, 0x52EA39C1U},
		{0, 0xB0806FF1U, 0xFBBD4FEAU},
		{0, 0xAB6BB069U, 0x89657D7FU},
		{0, 0xB614A6F2U, 0xA036F2DCU},
		{0, 0x2744A039U, 0x167ADE64U},
		{0, 0x93EAF72BU, 0x8739697AU},
		{0, 0xC1526D6FU, 0xE9A92D96U},
		{0, 0x59780225U, 0xDCA02EC5U},
		{0, 0x925D5259U, 0x37B842B4U},
		{0, 0xD3EA918EU, 0xFF258C79U},
		{0, 0x80D3799BU, 0x86C54965U},
	},
	{
		{0, 0x38BB02FDU, 0x57D19C15U},
		{0, 0xE6C79E74U, 0xF72C1511U},
		{0, 0xFAA13DDEU, 0xAEE18A08U},
		{0, 0x48628CBDU, 0xA31E148DU},
		{0, 0xC79D862FU, 0x0AEE1288U},
		{0, 0x64062ED6U, 0x5EE10D5EU},
		{0, 0x36B6DA6EU, 0x449D1509U},
		{0, 0xDDA2FA1FU, 0x1CA2F862U},
		{0, 0x6F1E11A7U, 0x8787A83AU},
		{0, 0x3280EA59U, 0xD6746BF1U},
		{0, 0x9BDD6034U, 0xC5D10BD0U},
		{0, 0x72DA079DU, 0x3533D08FU},
		{0, 0xD13EB738U, 0xAB696425U},
		{0, 0xF9E158BBU, 0xFF9FC7ABU},
		{0, 0x5EEC569BU, 0x4FECD69BU},
		{0, 0xF73E2965U, 0xCA33FCFAU},
	},
	{
		{0, 0xF18DADA4U, 0xA188D457U},
		{0, 0x14C6F690U, 0xBB2FA80EU},
		{0, 0xBFC7CAC1U, 0xD9794062U},
		{0, 0x7D13864FU, 0xABB1E192U},
		{0, 0x0FB203B2U, 0xFF1E582AU},
		{0, 0x9DE744B2U, 0x9617B047U},
		{0, 0x7FD90D37U, 0x6740F44DU},
		{0, 0x641681B7U, 0x549544F8U},
		{0, 0x6B698CB8U, 0x744FEADAU},
		{0, 0xC15988BFU, 0x4A03E7EEU},
		{0, 0x54978569U, 0x7280C230U},
		{0, 0x1C2B44FDU, 0x5C545790U},
		{0, 0x9D050387U, 0x01D124C7U},
		{0, 0x4BA0385FU, 0xF04C7A96U},
		{0, 0x0603E2C4U, 0x38783D7FU},
		{0, 0x4DE64225U, 0x463861E7U},
	}
};

/* 
	Hozzaadas a fahoz (vagy meglevo csucs frissitese)
	A rootot adja vissza
*/
PBIFA AddBifa(PBIFA root, unsigned hash, PJATEKALLAS jatek, PADAT adat)
{
	PFAADAT uj, futo;

	int i;

	/* Ha a fa levelere ertunk, vagy uj a fa */
	if (root == NULL) {
		if ((root = (PBIFA)malloc(sizeof(BIFA))) == NULL) {
			fprintf(stderr, "Elfogyott a memoria !\n");
			exit(-1);
		}
		root->hash = hash;
		root->bal = NULL;
		root->jobb = NULL;
		root->elso = NULL;
	} else if (hash < root->hash) {
		root->bal = AddBifa(root->bal, hash, jatek, adat);
		return root;
	} else if (hash > root->hash) {
		root->jobb = AddBifa(root->jobb, hash, jatek, adat);
		return root;
	}
	/* A hash egyezik, vagy uj fa */
	for (futo = root->elso; futo != NULL; futo = futo->kov) { /* Vegigfutunk a lancolt listan */
		for (i = 0; i < 16; i++) {
			if (futo->tabla[i] != jatek->tabla[i]) {
				goto next; /* Ha a tablak nem egyeznek a kovetkezore ugrunk */
			}
		}
		/* A tablak egyeztek, bemasoljuk az adatot */
		futo->adat = *adat;
		return root;
next:	;
	}
	/* Ha nem talalta meg a tablat, vagy uj fa */
	if ((uj = (PFAADAT)malloc(sizeof(FAADAT))) == NULL) {
		fprintf(stderr, "Elfogyott a memoria !\n");
		exit(-1);
	}
	/* Hozzafuzes a lancolt listahoz (az elejere) */
	uj->kov = root->elso;
	root->elso = uj;
	uj->adat = *adat;
	for (i = 0; i < 16; i++) {
		uj->tabla[i] = jatek->tabla[i];
	}
	return root;
}

/*
	Kereses a faban, adat-ba belemasolja, ha talalt valamit
	1-et ad vissza, ha megtalalta, es 0-t, ha nem
*/
int SearchBifa(PBIFA root, unsigned hash, PJATEKALLAS jatek, PADAT adat)
{
	PFAADAT futo;
	int i;

	if (root == NULL) { /* Nem talalta meg */
		return 0;
	}
	if (hash < root->hash) {
		return SearchBifa(root->bal, hash, jatek, adat);
	} else if (hash > root->hash) {
		return SearchBifa(root->jobb, hash, jatek, adat);
	}
	/* Megtalalta, kereses a lancolt listaban */
	for (futo = root->elso; futo != NULL; futo = futo->kov) {
		for (i = 0; i < 16; i++) {
			if (futo->tabla[i] != jatek->tabla[i]) {
				goto next; /* Ha a tablak nem egyeznek a kovetkezore ugrunk */
			}
		}
		/* A tablak egyeztek, elmentjuk az adatot */
		*adat = futo->adat;
		return 1;
next:	;
	}
	/* Nem talalta meg */
	return 0;
}

/* Egy csucshoz tartozo lancolt lista felszabaditasa */
static void DestroyList(PBIFA node)
{
	PFAADAT futo, tmp;

	/* A lancolt lista felszabaditasa */
	for (futo = node->elso; futo != NULL; futo = tmp) {
		tmp = futo->kov;
		free(futo);
	}
}

/* Fa felszabaditasa */
PBIFA DestroyBifa(PBIFA root)
{
	if (root == NULL) {
		return NULL;
	}
	root->bal = DestroyBifa(root->bal);
	root->jobb = DestroyBifa(root->jobb);
	DestroyList(root);
	free(root);
	return NULL;
}

PBIFA RefreshBifa(PBIFA root)
{
	PFAADAT lancfuto, elozo = NULL;
	PBIFA fafuto, faelozo, tmp;

	if (root == NULL) {
		return NULL;
	}
	root->bal = RefreshBifa(root->bal);
	root->jobb = RefreshBifa(root->jobb);
	for (lancfuto = root->elso; lancfuto != NULL; ) {
		lancfuto->adat.regi = 1;
		if (lancfuto->adat.vdepth > 2) {
			lancfuto->adat.vdepth -= 2;
			elozo = lancfuto;
			lancfuto = lancfuto->kov;
		} else {
			if (elozo != NULL) { /* Torolni kell a lancolt lista kozeperol */
				elozo->kov = lancfuto->kov;
				free(lancfuto);
				lancfuto = elozo->kov;
			} else if (elozo == NULL) { /* Torolni kell a lancolt lista elejerol */
				root->elso = lancfuto->kov;
				free(lancfuto);
				lancfuto = root->elso;
			}
		}
	}
	if (root->elso == NULL) { /* Ha kitoroltuk az egesz lancolt listat */
		/* Nincs gyereke */
		if (root->jobb == NULL && root->bal == NULL) {
			free(root);
			return NULL;
		}
		/* Csak jobb gyereke van */
		if (root->bal == NULL) {
			tmp = root->jobb;
			free(root);
			return tmp;
		}
		/* Csak bal gyereke van */
		if (root->jobb == NULL) {
			tmp = root->bal;
			free(root);
			return tmp;
		}
		/* Jobb es bal gyereke is van */
		/* Megkeressuk a root bal oldalanak legjobboldalibb elemet */
		faelozo = NULL;
		for (fafuto = root->bal; fafuto->jobb != NULL; faelozo = fafuto, fafuto = fafuto->jobb) {
			;
		}
		if (faelozo != NULL) {
			if (fafuto->bal == NULL) {
				faelozo->jobb = NULL;
			} else {
				faelozo->jobb = fafuto->bal;
			}
			fafuto->bal = root->bal;
		}
		fafuto->jobb = root->jobb;
		free(root);
		return fafuto;
	}
	return root;
}

/* Megszamolja hany pontja van a fanak */
int GetBifaNodeCount(PBIFA root)
{
	if (root == NULL) {
		return 0;
	}
	return GetBifaNodeCount(root->bal) + GetBifaNodeCount(root->jobb) + 1;
}

/* 
	Megszamolja hany jatekallas van eltarolva a faban, 
	nagy esellyel egyezik a pontok szamaval, ha a hashfuggveny eleg jo 
*/
int GetFullBifaCount(PBIFA root)
{
	PFAADAT futo;
	int db;

	if (root == NULL) {
		return 0;
	}
	for (futo = root->elso, db = 0; futo != NULL; futo = futo->kov, db++) {
		;
	}
	return GetFullBifaCount(root->bal) + GetFullBifaCount(root->jobb) + db;
}

/* Megszamolja a szintek szamat a faban */
int GetBifaLevelCount(PBIFA root)
{
	int bal, jobb;

	if (root == NULL) {
		return 0;
	}
	bal = GetBifaLevelCount(root->bal);
	jobb = GetBifaLevelCount(root->jobb);
	return (bal > jobb ? bal + 1 : jobb + 1);
}

/* Zobrist hashing */
unsigned ZobristHash(PJATEKALLAS jatek)
{
	int i, j;
	unsigned ret = zobalap;
	for (i = 0; i < jatek->SOR; i++) {
		for (j = 0; j < jatek->OSL; j++) {
			ret ^= zobtabla[i][j][GetTabla(jatek->tabla, i, j)];
		}
	}
	return ret;
}
