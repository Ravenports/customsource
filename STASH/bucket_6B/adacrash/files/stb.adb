with Ada.Text_IO;
with Ada.Exceptions;
with GNAT.Traceback.Symbolic;

procedure STB is

   use Ada;
   use Ada.Exceptions;
   
   package TRC renames GNAT.Traceback;

   procedure P1 is
      K : Positive := 1;
   begin
      K := K - 1;
   exception
      when E : others =>
         Text_IO.Put_Line (Exception_Information (E));
         declare
            trace : TRC.Tracebacks_Array (1 .. 2_000);
            trlen : Natural;
         begin
            TRC.Call_Chain (trace, trlen);
            Text_IO.Put_Line ("Dump of stack:");
            Text_IO.Put_Line (TRC.Symbolic.Symbolic_Traceback (trace (1 .. trlen)));
         end;
         Text_IO.Put_Line ("");
         Text_IO.Put_line ("Dump from Exception");
         Text_IO.Put_Line (TRC.Symbolic.Symbolic_Traceback (E));
   end P1;

   procedure P2 is
   begin
      P1;
   end P2;

begin
   P2;
end STB;
