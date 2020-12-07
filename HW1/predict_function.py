# -*- coding: utf-8 -*-
import numpy as np 
from math import log

def read_pinyin_table(table_path):
    f=open(table_path,'r',encoding='gbk')
    dic={}
    for line in f.readlines():
        line=line.split()
        dic[line[0]]=line[1:]
    return dic

def read_hanzi_table(table_path):
    f=open(table_path,'r',encoding='gbk')
    lis=[]
    line=f.readline()
    for word in line:
        lis.append(word)
    return lis



def get_sum(hanzi_table,word_dict):
	n_sum=0
	for i in hanzi_table:
		if i in word_dict:
			n_sum=n_sum+word_dict[i]
 
	return n_sum

def getProbability_word(i,word_dict,n_sum):
	if i not in word_dict:
		p_word=0
	else:
		p_word=word_dict[i]/n_sum

	return p_word

def getProbability_pair(i,j,word_dict,pair_dict):
	pair=i+j
	if pair in pair_dict:
		n_pair=pair_dict[pair]
		p=n_pair/word_dict[i]
		return p 

	else:
		return 0

def revise_probability_pair(i,j,alpha,word_dict,pair_dict,n_sum):
	p=alpha*getProbability_pair(i,j,word_dict,pair_dict)+(1-alpha)*getProbability_word(i,word_dict,n_sum)

	return p 


def breadth_first_search(line,word_dict,pair_dict,pinyin_table,alpha,n_sum):
	items=line.split()
	N=len(items)
	index=[]
	P=[]
	for i in range(len(pinyin_table[items[0]])):
		index.append([i])
		temp=getProbability_word(pinyin_table[items[0]][i],word_dict,n_sum)
		if temp==0:
			P.append(-float("inf"))
		else:
			P.append(log(temp))
		
		
	for i in range(1,N,1):
		n=len(index)
		j=0
		while j<n:
			for k in range(len(pinyin_table[items[i]])):
				index.append(index[j]+[k])
				temp=revise_probability_pair(pinyin_table[items[i-1]][index[j][-1]],
					pinyin_table[items[i]][k],
					alpha,word_dict,pair_dict,n_sum)
				if temp==0:
					P.append(P[j]-float('inf'))
				else:
					P.append(P[j]+log(temp))
			j=j+1
		index=index[n:]
		P=P[n:]

	return index,P



def dynamicplanning(line,word_dict,pair_dict,pinyin_table,alpha,n_sum):
	items=line.split()
	N=len(items)
	index=[]
	P=[]
	for i in range(len(pinyin_table[items[0]])):
		temp=getProbability_word(pinyin_table[items[0]][i],word_dict,n_sum)
		P.append(temp)
		index.append([i])
		
	for i in range(1,N,1):
		n=len(index)
		#new character
		for k in range(len(pinyin_table[items[i]])):
		    #before sentence
			j=0
			P_temp=[]
			index_temp=[]
			while j<n:
				temp=revise_probability_pair(pinyin_table[items[i-1]][index[j][-1]],
					pinyin_table[items[i]][k],
					alpha,word_dict,pair_dict,n_sum)
				P_temp.append(P[j]*temp)
				index_temp.append(index[j]+[k])
				j=j+1
			max_index=P_temp.index(max(P_temp))
			P.append(P_temp[max_index])
			index.append(index_temp[max_index])
		index=index[n:]
		P=P[n:]
		

	return index,P



def get_final(line,index,P,pinyin_table):
	items=line.split()
	max_index=index[np.argmax(P)]
	line_trans=''
	for i in range(len(max_index)):
		line_trans=line_trans+pinyin_table[items[i]][max_index[i]]

	return line_trans




