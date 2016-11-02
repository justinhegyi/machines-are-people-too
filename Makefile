CC = g++
CFLAGS = -std=c++11 -Wall -g
#CFLAGS = -std=c++0x -Wall -g
#CFLAGS = -Wall -g
SRCS = jmh361.cpp Attribute.cpp NumericAttribute.cpp AttributeFactory.cpp Attributes.cpp NominalAttribute.cpp Dataset.cpp TrainTestTets.cpp Example.cpp Examples.cpp Performance.cpp Evaluator.cpp Classifier.cpp KNN.cpp NB.cpp ID3Node.cpp ID3.cpp RDF.cpp

OBJS = ${SRCS:.cpp=.o}

a.out: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)

$(OBJS):
	$(CC) $(CFLAGS) -c $*.cpp

depend:
	$(CC) -MM $(SRCS) > Makefile.dep

Makefile.dep:
	touch Makefile.dep

clean:
	rm -f $(OBJS) a.out core

include Makefile.dep

