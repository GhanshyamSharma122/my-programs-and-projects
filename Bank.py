import json
import os
def create():
	try:
		a=open('a.dat','r')
	except IOError:
		a=open('a.dat','w')
	try:
		dat=json.loads(a.read())
		acc=dat[-1]['acc']+1
	except:
		dat=list()
		acc=0
	a.close()
	s={
	'name':input("enter name "),
	'age':int(input("enter age ")),
	'address':input('enter the address '),
	'deposit':int(input("enter the deposit ")),
	'pin':int(input("enter the pin ")),
	'acc':acc,
	'loan':0
	}
	dat.append(s)
	print("account successfully created\nyour account no is ",)
	a=open('a.dat','w')
	a.write(json.dumps(dat))
def loan(acc,pin):
	a=open('a.dat','r')
	dat=json.loads(a.read())
	a.close()
	details(acc,pin)
	for i in dat:
		if i['acc']==acc and i['pin']==pin:
			if (i['loan']==0):
				w=int(input('enter the amount you want loan '))
				if(w<2000000):
					i['loan']=w
					print("loan amount succesfully taken")
				else:
					print('loan should not exceed 2000000')
		
	a=open('a.dat','w')
	a.write(json.dumps(dat))
def loanClear(acc,pin):
	a=open('a.dat','r')
	dat=json.loads(a.read())
	a.close()
	details(acc,pin)
	for i in dat:
		if (i['acc']==acc and i['pin']==pin and i['loan']!=0):
			print('you have loan')
			a=int(input('enter the amount you want to pay loan '))
			if(a==i['loan']):		
				i['loan']-=a
				print("loan cleared")
			else:
				i['loan']-=a
				print("you have reduced loan by",a,"amount","remaining loan",i['loan'])
		else:
				print('loan not taken')

				
	a=open('a.dat','w')
	a.write(json.dumps(dat))

def details(acc,pin):
	a=open('a.dat','r')
	found=False
	dat=json.loads(a.read())
	a.close()
	for i in dat:
		if i['acc']==acc and i['pin']==pin:
			del i['pin']
			found =True
			print(i)
	if not found:
		print("not found")
		return False
def deposit(acc,pin):
	a=open('a.dat','r')
	dat=json.loads(a.read())
	a.close()
	details(acc,pin)
	for i in dat:
		if i['acc']==acc and i['pin']==pin:
			i['deposit']+=int(input('enter the amount you want to deposit '))
			print("money succesfully deposited")
		
	a=open('a.dat','w')
	a.write(json.dumps(dat))

def withdraw(acc,pin):
	a=open('a.dat','r')
	dat=json.loads(a.read())
	a.close()
	details(acc,pin)
	for i in dat:
		if i['acc']==acc and i['pin']==pin:
			a=int(input('enter the amount you want to withdraw '))
			if(a<=i['deposit']):		
				i['deposit']-=a
				print("money succesfully withdrawn")
			else:
				print("your withdraw amounts exceeds the amount you have in your balance")
				
	a=open('a.dat','w')
	a.write(json.dumps(dat))

def transfer(acc,pin,acc1):
	found =False
	a=open('a.dat','r')
	dat=json.loads(a.read())
	a.close()
	details(acc,pin)
	for i in dat:
		if i['acc']==acc and i['pin']==pin:
			for j in dat:
				if j['acc']==acc and j['pin']==pin:
					found =True
			a=int(input('enter the amount you want to transfer '))
			if(a<=i['deposit']):		
				i['deposit']-=a
				j['deposit']+=a
				print("money succesfully transfered")
			else:
				print("your transfer amounts exceeds the amount you have in your balance")
	if not found:
		print("the account you are transferring does not exists")	
				
	a=open('a.dat','w')
	a.write(json.dumps(dat))

def remove(acc,pin):
	a=open('a.dat','r')
	dat=json.loads(a.read())
	a.close()
	for i in dat:
		if i['acc']==acc and i['pin']==pin:
			del dat[dat.index(i)]
			print("account sucessfully removed")
	a=open('a.dat','w')
	a.write(json.dumps(dat))
while True:
	os.system("clear")
	a=int(input('''
Ghanshyam Bank Limited
1.create account
2.remove account
3.deposit
4.withdraw
5.bank balance
6.transfer
7.loan
8.loanClear
enter your choice
'''))

	if a==1:
		create()
	elif a==2:
		remove(int(input("enter the account number ")),int(input("enter the pin ")))
	elif a==3:
		deposit(int(input("enter the account number ")),int(input("enter the pin ")))
	elif a==4:
		withdraw(int(input("enter the account number ")),int(input("enter the pin ")))
	elif a==5:
		details(int(input("enter the account number ")),int(input("enter the pin ")))
	elif a==6:
		transfer(int(input("enter the account number ")),int(input("enter the pin ")),int(input("enter the target account number ")))
	elif a==7:
		loan(int(input("enter the account number ")),int(input("enter the pin ")))
	elif a==8:
		loanClear(int(input("enter the account number ")),int(input("enter the pin ")))	
	else:
		print("wrong choice")
	input("press enter to continue")
	