#include "common.h"
#include "terminal.h"
#include "terminal_backend_b8000.h"

// Thanks to Karol Grzybowski
typedef struct TrapFrame {
  uint64_t r15;
  uint64_t r14;
  uint64_t r13;
  uint64_t r12;
  uint64_t r11;
  uint64_t r10;
  uint64_t r9;
  uint64_t r8;
  uint64_t rbp;
  uint64_t rdi;
  uint64_t rsi;
  uint64_t rdx;
  uint64_t rcx;
  uint64_t rbx;
  uint64_t rax;
  uint64_t rsp;

  /*uint64_t trap_number;
    uint64_t error_code;*/

  uint64_t rip;
  uint64_t segment_cs;
  /*uint64_t rflags;
    uint64_t rsp;
    uint64_t segment_ss;*/

} TrapFrame;

void GuruPanicOfDeath(const char *reason, TrapFrame *frame) {
  TerminalBackend *con = TerminalBackendB8000();
  T_ClearScreen(con);

  T_SetColor(con, COLOR_WHITE, 0, 0);
  T_PutText(con, "\n Opsy!");
  T_SetColor(con, COLOR_LIGHT_MAGENTA, 0, 0);
  T_PutText(con, "\t\t\t\t  GynOS\n\n");
  T_SetColor(con, COLOR_GRAY, 0, 0);
  T_PutText(con, " Something went wrong!\n\n\n");

  T_SetColor(con, COLOR_YELLOW, 0, 0);
  T_PutText(con, " State:\n\n");

  T_Printf(con, "  RAX: %x\t\t R8: %x\n", frame->rax, frame->r8);
  T_Printf(con, "  RBX: %x\t\t R9: %x\n", frame->rbx, frame->r9);
  T_Printf(con, "  RCX: %x\t\t R10: %x\n", frame->rcx, frame->r10);
  T_Printf(con, "  RDX: %x\t\t R11: %x\n", frame->rdx, frame->r11);
  T_Printf(con, "  RSI: %x\t\t R12: %x\n", frame->rsi, frame->r12);
  T_Printf(con, "  RDI: %x\t\t R13: %x\n", frame->rdi, frame->r13);
  T_Printf(con, "  RBP: %x\t\t R14: %x\n", frame->rbp, frame->r14);
  T_Printf(con, "  RSP: %x\t\t R15: %x\n", frame->rsp, frame->r15);

  T_SetColor(con, COLOR_RED, 0, 0);
  T_PutText(con, "\n CS:RIP: ");
  T_SetColor(con, COLOR_LIGHT_RED, 0, 0);
  T_Printf(con, "%x:%x\n\n", frame->segment_cs, frame->rip);

  T_SetColor(con, COLOR_LIGHT_RED, 0, true);
  T_PutText(con, "\n\n Reason: ");
  T_Printf(con, "%s\n\n", reason);

  for (;;)
    ;
}

void Int_DE(TrapFrame *frame) {
  GuruPanicOfDeath("DIVISION_ERROR", frame);
}
