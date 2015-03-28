class Message 
{
	public:
		int from;
		int content;
		int recipient;

		Message (int c, int f, int r)
		{
			content = c;
			from = f;
			recipient = r;
		}


};