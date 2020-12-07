import numpy as np 
import random
from sklearn.model_selection import train_test_split
import tensorflow as tf 



def one_hot(data):
	mat=np.zeros([len(data),10])
	for i in range(len(mat)):
		mat[i][data[i]]=1
	return mat 

def process_data(trainfile_path):
	data=np.loadtxt(open(trainfile_path),delimiter=',',skiprows=1,dtype=int)
	train,valid=train_test_split(data,test_size=0.2)
	train_x,train_y=train[:,1:],train[:,0]
	valid_x,valid_y=valid[:,1:],valid[:,0]

	train_x=train_x/255.0
	valid_x=valid_x/255.0
	train_y=one_hot(train_y)
	valid_y=one_hot(valid_y)
	return train_x,train_y,valid_x,valid_y




def conv2D(input,weight_shape,bias_shape):
	weight_init=tf.truncated_normal_initializer(stddev=0.1)
	W=tf.get_variable("W",weight_shape,initializer=weight_init)
	bias_init=tf.constant_initializer(0.0)
	b=tf.get_variable("b",bias_shape,initializer=bias_init)
	return tf.nn.relu(tf.nn.bias_add(tf.nn.conv2d(input,W,strides=[1,1,1,1],padding='SAME'),b)) 

def max_pooling(input,k=2):
	return tf.nn.max_pool(input,ksize=[1,k,k,1],strides=[1,k,k,1],padding='SAME')

def layer(input,weight_shape,bias_shape):
	weight_init=tf.truncated_normal_initializer(stddev=0.1)
	bias_init=tf.constant_initializer(0.0)
	W=tf.get_variable("W",weight_shape,initializer=weight_init)
	b=tf.get_variable("b",bias_shape,initializer=bias_init)
	return tf.nn.relu(tf.matmul(input,W)+b)

def inference(x,keep_prob):
	x=tf.reshape(x,shape=[-1,28,28,1])
	with tf.variable_scope("conv_1"):
		conv_1=conv2D(x,[5,5,1,32],[32])
		pool_1=max_pooling(conv_1)

	with tf.variable_scope("conv_2"):
		conv_2=conv2D(pool_1,[5,5,32,64],[64])
		pool_2=max_pooling(conv_2)

	with tf.variable_scope("conv_3"):
		conv_3=conv2D(pool_2,[5,5,64,128],[128])
		pool_3=max_pooling(conv_3)


	with tf.variable_scope("fc"):
		pool_3_flat=tf.reshape(pool_3,[-1,4*4*128])
		fc_1=layer(pool_3_flat,[4*4*128,1024],[1024])
		fc_1_drop=tf.nn.dropout(fc_1,keep_prob)

	with tf.variable_scope("output"):
		output=tf.nn.softmax(layer(fc_1_drop,[1024,10],[10]))
	
	
	return output



if __name__=="__main__":
	epochnum=20
	batch_size=100
	learning_rate=1e-4
	train_x,train_y,valid_x,valid_y=process_data('./train.csv')
	
	with tf.Session() as sess:
		x=tf.placeholder("float",[None,784],name="x")
		y=tf.placeholder("float",[None,10],name="y")
		keep_prob=tf.placeholder(tf.float32,name="keep_prob")

		output=inference(x,keep_prob)
		output_labels = tf.argmax(output,1,name='output_labels')

		cost=-tf.reduce_sum(y*tf.log(output))

		optimizer=tf.train.AdamOptimizer(learning_rate)
		train_op=optimizer.minimize(cost)

		correction_prediction=tf.equal(tf.argmax(output,1),tf.argmax(y,1))
		eval_op=tf.reduce_mean(tf.cast(correction_prediction,"float"))

		sess.run(tf.global_variables_initializer())

		saver=tf.train.Saver()

		batchnum=int(len(train_x)/batch_size)
		

		for i in range(epochnum):
			train_index=list(range(len(train_x)))
			random.shuffle(train_index)
			start=0
			
			for j in range(batchnum):
				index_temp=train_index[start:start+batch_size]
				batch_x,batch_y=train_x[index_temp],train_y[index_temp]
				sess.run(train_op,feed_dict={x:batch_x,y:batch_y,keep_prob:0.5 })
				start=start+batch_size
				#accuracy=sess.run(eval_op,feed_dict={x:batch_x,y:batch_y,keep_prob:1.0})
				#print(j,accuracy)

			accuracy=sess.run(eval_op,feed_dict={x:train_x,y:train_y,keep_prob:1.0})
			print(i,accuracy)
			accuracy=sess.run(eval_op,feed_dict={x:valid_x,y:valid_y,keep_prob:1.0})
			print(i,accuracy)
			saver_path=saver.save(sess,"./ckpt/my_model.ckpt",global_step=batchnum*(i+1))
			



			

				

				
		
		













