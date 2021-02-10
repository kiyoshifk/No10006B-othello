



/********************************************************************************/
/*		initban																	*/
/********************************************************************************/
int initban(char *ban)
{
	int x, y, p;
	
	memset(ban, ISHI_O, 100);
	for(x=1; x<=8; x++){
		for(y=1; y<=8; y++){
			p = macropos(x,y);
			ban[p] = ISHI_N;
		}
	}
	ban[macropos(4,4)] = ISHI_S;
	ban[macropos(5,5)] = ISHI_S;
	ban[macropos(4,5)] = ISHI_K;
	ban[macropos(5,4)] = ISHI_K;
}
/********************************************************************************/
/*		MCrnd																	*/
/********************************************************************************/
long MCrnd(long i)
{
	rnd_init = rnd_init * 1234567 + 123456781;
	return rnd_init % i;
}
/********************************************************************************/
/*		game_init																*/
/********************************************************************************/
int game_init()
{
	initban(goban);
	tekazu = 1;
	teban = ISHI_K;
//	white = 0;
//	black = 0;
}
/********************************************************************************/
/*		yomitst																	*/
/********************************************************************************/
int yomitst_s(char *ban, int k, int pos, int dir)
{
	int kk;
	
	if(ban[pos])							// �Ζ����łȂ����
		return 0;							// �łĂȂ�
	pos += dir;
	if(ban[pos] != macroinv(k))				// �G��ɐڐG���Ă��Ȃ����
		return 0;							// �łĂȂ�
	for(;;){
		pos += dir;
		kk = ban[pos];
		if(kk==k)							// �͂���ł���
			return 1;						// �łĂ�
		if(kk==ISHI_N || kk== ISHI_O)
			return 0;						// �łĂȂ�
	}
}

int yomitst(char *ban, int k, int pos)
{
	int i;
	
	if(ban[pos])							// �Ζ����łȂ����
		return 0;							// �łĂȂ�
	for(i=0; i<8; i++){
		if(yomitst_s(ban, k, pos, dir3[i]))	// dir3 �����őłĂ邩�H
			return 1;						// �łĂ�
	}
	return 0;								// �łĂȂ�
}

/********************************************************************************/
/*		get_upos																*/
/********************************************************************************/
int get_upos(char *ban, int k, char *upos, int *upos_cnt)
{
	int p;
	
	*upos_cnt = 0;
	for(p=10; p<81; p++){
		if(yomitst(ban, k, p)){				// �łĂ邩�H
			upos[(*upos_cnt)++] = p;
		}
	}
}

//		���̔Ֆʂɑł肪���邩�H
int upos_tst(char *ban, int k)
{
	char upos[60];
	int upos_cnt;
	
	get_upos(ban, k, upos, &upos_cnt);
	if(upos_cnt==0)
		return 0;								// �łĂȂ�
	return 1;									// �łĂ�
}
/********************************************************************************/
/*		yomiutu																	*/
/*		�J���x��Ԃ�															*/
/********************************************************************************/
int yomiutu(char *ban, int k, int pos)
{
	int i, j, s, p, dir, kaiho;
	
	s = macroinv(k);
	kaiho = 0;
	for(i=0; i<8; i++){
		dir = dir3[i];
		if(yomitst_s(ban, k, pos, dir)){	// dir �����őłĂ邩�H
			p = pos;
			for(;;){
				p += dir;
				if(ban[p]==s){
					ban[p] = k;
					for(j=0; j<8; j++){
						if(ban[p+dir3[j]]==ISHI_N)
							++kaiho;
					}
				}
				else{
					break;
				}
			}
		}
	}
	ban[pos] = k;
	return kaiho;
}
/********************************************************************************/
/*		result																	*/
/*		�ΐ��𐔂���A��+														*/
/********************************************************************************/
int result(char *ban)
{
	int ten, p;
	
	ten = 0;
	for(p=10; p<81; p++){
		if(ban[p]==ISHI_K)
			++ten;
		else if(ban[p]==ISHI_S)
			--ten;
	}
	return ten;
}
/********************************************************************************/
/*		game																	*/
/*		�Q�[���i�s�̃��C�����[�`��												*/
/********************************************************************************/
int game()
{
	int player;								// 0:cpu, 1:human
	int pos, ten;
	long eva;
	
	memset((char *)VIDEO, 0, sizeof(uint)*320*20);		// clear
	strcpy(msg1, white ? "white: human       " : "white: cpu        ");
	strcpy(msg2, black ? "black: human       " : "black: cpu        ");
	pos = macropos(1,1);
	for(;;){
		/***	�p�X�̏���	***/
		if(upos_tst(goban, teban)==0){		// �łĂȂ�
			teban = macroinv(teban);
			if(upos_tst(goban, teban)==0){	// ����Ԃł��łĂȂ�
				ten = result(goban);
				if(ten==0)
					strcpy(msg3, "End: Draw       ");
				else{
					msg3[0] = 0;
					strcpy(msg3, ten>0 ? "Black win " : "White win ");
					strcat(msg3, l_to_a(abs1(ten)));
				}
				dispban(goban, pos);
				ut_getc();				// get 1 charactor
				return;
			}
			strcpy(msg3, "=== utenai ===    ");
            dispban(goban, pos);
			ut_getc();				// get 1 charactor
		}
		player = teban==ISHI_K ? black : white;
		if(player==0){						// cpu �̎��
			if(teban==ISHI_K) strcpy(msg3, "B thinking           ");
			else              strcpy(msg3, "W thinking           ");
			dispban(goban, pos);
			pos = gametop(&eva);
			if(yomitst(goban, teban, pos)==0)
				Dispbug();
		}
		else{								// �l�Ԃ̎��
			strcpy(msg3, teban==ISHI_K ? "B: Please play     " : "W: Please play      ");
			for(;;){
				dispban(goban, pos);
				while ((pos = human_input(pos)) == 0) ;
				if (yomitst(goban, teban, pos))
					break;
				strcpy(msg3, "Illegal move      ");
			}
		}
        if(brink_flag){
            brinking(teban, pos);
        }
		yomiutu(goban, teban, pos);
		teban = macroinv(teban);
		++tekazu;
	}
}
/********************************************************************************/
/*		gametop																	*/
/********************************************************************************/
#define INF 10000000


long evaluate(char *ban, int k, long *tenpat, long gamma, int kaiho)
{
	long ten;
	int p;
	
	++eva_cnt;
	ten = 0;
	for(p=10; p<81; p++){
		if(ban[p]==ISHI_K)
			ten += tenpat[p];
		else if(ban[p]==ISHI_S)
			ten -= tenpat[p];
	}
	if(teban <= 15){
		ten += MCrnd(40)-20;				// �������Z
	}
	ten = k==ISHI_K ? ten : -ten;

	ten += 20*gamma;
	ten += 10*kaiho;
	return ten;
}

long negamax(char *ban, int k, int depth, int maxdepth, int *pos, long alpha, long beta, int pass, long gamma, int kaiho)
{
	int i, upos_cnt, dummy, kho;
	char ban1[100], upos[60];
	long ten, max;
	
	if(depth>=maxdepth){
		return evaluate(ban, k, tenpat_std, gamma, kaiho);	/* ���ԕ]���֐�						*/
	}
	
	max = -INF;
	*pos = 0;
	get_upos(ban, k, upos, &upos_cnt);
	if (upos_cnt == 0){
		if (pass){												// 2��A���p�X
			return evaluate(ban, k, tenpat_end, gamma, kaiho);	/* ���ԕ]���֐�						*/
		}
		return -negamax(ban, macroinv(k), depth + 1, maxdepth, &dummy, -beta, -alpha, 1, -gamma, -kaiho);
	}
//	if(maxdepth-depth >= 4 && upos_cnt >= 2)
//		sort_upos(ban, k, depth+4, maxdepth, upos, upos_cnt);
	gamma = gamma/2 + upos_cnt;
	for(i=0; i<upos_cnt; i++){
		memcpy(ban1, ban, 100);
		if(yomitst(ban1, k, upos[i])==0)			/* �łĂȂ�					*/
			continue;
		kho = yomiutu(ban1, k, upos[i]);
		if(depth<=1)
			kho = kho-kaiho;
		else
			kho = -kaiho;

		ten = - negamax(ban1, macroinv(k), depth+1, maxdepth, &dummy, -beta, -alpha, 0, -gamma, kho);
		if(ten > beta)							/* �}��							*/
			return ten;
		if(max < ten){
			*pos = upos[i];
			max = ten;
			if(max > alpha)
				alpha = max;
		}
	}
	return max;
}

int gametop(long *pten)
{
	int maxdepth, pos;
	long time1, ten;
	
	eva_cnt = 0;
//	maxdepth = 7;
	time1 = GetTickCount();
	for(maxdepth=1; maxdepth<=10; ++maxdepth){
		ten = negamax(goban, teban, 0, maxdepth, &pos, -INF, INF, 0, 0, 0);
		if(GetTickCount()-time1 > timesetting)
			break;
	}
//	msg_main_printf("depth=%d %ldms ten=%ld cnt=%ld", maxdepth, GetTickCount()-time1, ten, eva_cnt);
	*pten = ten;
	return pos;
}
/********************************************************************************/
/*		sort_upos																*/
/********************************************************************************/
//struct data {long ten; char upos;};
//
//int cmp_upos(const int *a, const int *b)
//{
//	struct data *aa = (struct data *)a;
//	struct data *bb = (struct data *)b;
//	
//	if(aa->ten==bb->ten)
//		return 0;
//	if(aa->ten > bb->ten)
//		return -1;
//	return 1;
//}
//
//int sort_upos(struct v *v, char *ban, int k, int depth, int maxdepth, char *upos, int upos_cnt)
//{
//	struct data data[60];
//	int i, dummy, kaiho;
//	char ban1[100];
//	
//	for(i=0; i<upos_cnt; i++){
//		data[i].upos = upos[i];
//		memcpy(ban1, ban, 100);
//		kaiho = yomiutu(v, ban1, k, upos[i]);
//		data[i].ten = -negamax(v, ban1, macroinv(k), 1, maxdepth-depth+1, &dummy, -INF, INF, 0, 0, kaiho);
//	}
//	qsort(data, upos_cnt, sizeof(struct data), cmp_upos);
//	for(i=0; i<upos_cnt; i++){
//		upos[i] = data[i].upos;
//	}
//}
